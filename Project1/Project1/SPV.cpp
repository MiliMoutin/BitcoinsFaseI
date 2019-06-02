#include "SPV.h"
#include <chrono>
#include <thread>

using namespace std::this_thread; 
using namespace std::chrono; 

void SPV::attach(Node* s) {
	this->neighbours.push_back(s);
	notifyAllObservers();
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
				UTXO to_push(o.getAmount(), t.getId());
				this->UTXOs.push_back(to_push);
				this->roots.push_back(h.getRoot());
			}
		}

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
		for (PathElement id : iterpaths->getPath()){
			if (id.getLoF() == RIGHT) {
				string auxstr = to_string(txID) + to_string(id.getId());
				txID = generateIDString(auxstr);
				cout << "IdGeneration..." << txID << endl;
			}
			if (id.getLoF() == LEFT) {
				string auxstr = to_string(id.getId()) + to_string(txID);
				txID = generateIDString(auxstr);
				cout << "IdGeneration..." << txID << endl;

			}
		}
		//si el ID generado es igual al root devuelve falso
		if (txID != hb.getRoot()->getID()) {
			cout << "no valida" << endl;
			sleep_for(seconds(30));
			return false;
		}
 	}
	cout << "valida" << endl;
	sleep_for(seconds(30));
	return true;
}





