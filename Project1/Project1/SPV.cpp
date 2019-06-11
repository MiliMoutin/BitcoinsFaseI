#include "SPV.h"
#include <chrono>
#include <thread>
#define BLOCKID 3761265367

using namespace std::this_thread; 
using namespace std::chrono; 

void SPV::attach(Node* s) {
	this->neighbours.push_back(s);
	notifyAllObservers();
}

bool SPV::isNeighbour(string id) {
	if (this->neighbours.empty()) {
		return false;
	}
	for (Node *n : this->neighbours) {
		if (n->getID() == id) {
			return true;
		}
		return false;
	}
}

void SPV::askForHeader() {
	vector<Full*>::iterator iter;
	for (Node* n : this->neighbours) {
		if (n->getType() == "Full") {
			Full* neighbour = (Full*)n;
			if (!neighbour->emptyBlockchain()) {
				HeaderBlock header = neighbour->askForHeader();
				if (!headerPresent(header.getBlockId())) {
					this->headers.push_back(header);
				}
			}
		}
	}
}

bool SPV::headerPresent(unsigned long headerID) {
	for (HeaderBlock b : this->headers) {
		if (b.getBlockId() == headerID) {
			return true;
		}
	}
	return false;

}

void SPV::notify(EDAMerkleBlock md, HeaderBlock h) {
	//aca deberia buscar el header por otro lado
	if (validNotification(md, h)) {
		//guardo las UTXOs 
		for (Transaction t : md.getTransactions()) {
			for (Output o : t.getOutputs()) {
				if (o.getIdReceiver() == this->id) {
					UTXO to_push(o.getAmount(), getUTXOId(o.getAmount(), o.getIdReceiver(), t.getId()));
					this->UTXOs.push_back(to_push);
				}
			}
		}
		this->roots.push_back(h.getRoot());

	}
}


bool SPV::validNotification(EDAMerkleBlock edamb, HeaderBlock hb) {

	list<Path> paths = edamb.getPaths();
	list<Transaction> transactions = edamb.getTransactions();

	list<Path>::iterator iterpaths;
	list<Transaction>::iterator itertxs;

	//itero paths y transacciones y voy validando que llegue al MerkleRoot
	for (iterpaths = paths.begin(), itertxs = transactions.begin(); iterpaths != paths.end(); iterpaths++, itertxs++) {
		unsigned long txID = itertxs->getId();
		cout << endl;

		//Itero un path para ver si puedo generar el MB
		for (PathElement id : iterpaths->getPath()) {
			if (id.getLoF() == RIGHT) {
				string auxstr = to_string(txID) + to_string(id.getId());
				txID = generateIDString(auxstr);

				if (id.getLoF() == LEFT) {
					string auxstr = to_string(id.getId()) + to_string(txID);
					txID = generateIDString(auxstr);

				}
			}
			//si el ID generado es igual al root devuelve falso
			if (txID != hb.getRoot()->getID()) {
				return false;
			}
		}

		return true;
	}
}

bool SPV::createTx(string idReceiver, double amount) {
	if (canDoTx(amount)) {
		/*En collector voy a guardar las transacciones necesarias*/
		list<UTXO> collector;
		double amountCollected = 0;
		list<UTXO>::iterator ptr;

		/*Busco UTXO hasta que llegue al monto que quiero*/
		for (ptr = UTXOs.begin(); ptr != UTXOs.end() && amountCollected < amount; ptr++) {
			amountCollected += ptr->getAmount();
			collector.push_back(*ptr);
		}

		/*Ahora creo la transacción*/
		/*Primero creo lo vector de input y outputs*/
		amountCollected = amount;
		vector<Input> impColector;
		vector<Output> outColector;
		for (UTXO u : collector) {
			if (u.getAmount() >= amountCollected) {
				impColector.push_back(Input(BLOCKID, u.getUTXOId()));
				outColector.push_back(Output(idReceiver, amountCollected));
				/*Si la UXTO es más grande, entocnes me mando a mi mismo lo que sobra*/
				outColector.push_back(Output(this->id, amountCollected - u.getAmount()));
			}
			else {
				impColector.push_back(Input(BLOCKID, u.getUTXOId()));
				outColector.push_back(Output(idReceiver, u.getAmount()));
				amountCollected - u.getAmount();
			}
		}

		/*Comunico al tx a mis vecinos Full*/
		CommunicateTx(Transaction(impColector, outColector));
	}

}


bool SPV::canDoTx(double amount) {
	double amountCollected = 0;
	list<UTXO>::iterator ptr;
	bool found = false;
	for (ptr = UTXOs.begin(); ptr != UTXOs.end() && !found; ptr++) {
		amountCollected += ptr->getAmount();
		if (amountCollected >= amount) {
			found = true;
		}
	}
	return false;
}

void SPV::CommunicateTx(Transaction t) {
	//transformo mi tx a un json
	nlohmann::json tx;
	tx=t.tranformToJson();
	for (Node* n : this->neighbours) {
		if (n->getType() == "Full" || n->getType() == "Miner") {
			Full* node = (Full*)n;
			node->receiveTx(tx);
		}
	}
}

unsigned long SPV::getUTXOId(double amount, string idReceiver, unsigned long txid) {
	string base = "";
	base += to_string(amount) + idReceiver + to_string(txid);
	return generateIDString(base);
}












