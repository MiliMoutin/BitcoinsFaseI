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

bool SPV::headerPresent(string headerID) {
	for (HeaderBlock b : this->headers) {
		if (b.getBlockId() == headerID) {
			return true;
		}
	}
	return false;

}

void SPV::notify(nlohmann::json EDAmb, nlohmann::json head) {
	EDAMerkleBlock md(EDAmb);
	HeaderBlock h(head);
	//aca deberia buscar el header por otro lado
	if (validNotification(md, h)) {
		//guardo las UTXOs 
		for (Transaction t : md.getTransactions()) {
			for (Output o : t.getOutputs()) {
				if (o.getIdReceiver() == this->id) {
					double amo = o.getAmount();
					UTXO to_push(UTXO(amo, to_string(this->getUTXOId(o.getAmount(), o.getIdReceiver(), t.getId()))));
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
		string txID = itertxs->getId();

		//Itero un path para ver si puedo generar el MB
		for (PathElement id : iterpaths->getPath()) {
			if (id.getLoF() == RIGHT) {
				string auxstr =txID +id.getId();
				txID = generateIDString(auxstr);

				if (id.getLoF() == LEFT) {
					string auxstr = id.getId() +txID;
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

void SPV::makeTx(string idReceiver, double amount) {
		/*Comunico al tx a mis vecinos Full*/
	if (Node::canDoTx(amount)) {
	Node::makeTx(idReceiver, amount);
	Node::signTx(Node::to_send);
	this->CommunicateTx(Node::to_send);
	}

}

void SPV::CommunicateTx(Transaction t) {
	for (Node* n : this->neighbours) {
		Full* f = (Full*)n;
		ECDSA<ECP, SHA256>::PublicKey pk;
		pk = this->getPk();
		f->receiveTx(t.tranformToJson(), this,pk);
	}
}



