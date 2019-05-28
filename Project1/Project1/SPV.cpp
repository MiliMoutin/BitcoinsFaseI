#include "SPV.h"
#include <chrono>
#include <thread>

using namespace std::this_thread; 
using namespace std::chrono; 

void SPV::attach(SPV* s) {
	this->neighboursSPV.push_back(s);
}


void SPV::attach(Full* s) {
	this->neighboursFull.push_back(s);
}

void SPV::askForHeader() {
	vector<Full*>::iterator iter;
	for (const auto& neighbour : neighboursFull) {
		if (!neighbour->emptyBlockchain()) {
			HeaderBlock header = neighbour->askForHeader();
			if (!headerPresent(header.getBlockId())) {
				this->headers.push_back(header);
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
		cout << "notificado";
		if (validNotification(md,h)) {
			//guardo las UTXOs 
			for (Transaction t : md.getTransactions()) {
				UTXO to_push(t.amountOutput(), t.getUTXOId());
				this->UTXOs.push_back(to_push);
				this->roots.push_back(h.getRoot());
			}
		}

	}


bool SPV::validNotification(EDAMerkleBlock edamb, HeaderBlock hb) {

	list<Path> paths = edamb.getPaths();
	list<Transaction> transactions = edamb.getTransactions();

	list<Path>::iterator iterpaths;
	list<Transaction>::iterator itertxs;

	for (iterpaths = paths.begin(), itertxs = transactions.begin(); iterpaths != paths.end(); iterpaths++, itertxs++) {
		unsigned long txID = itertxs->getId();

		//Itero un path para ver si puedo generar el MB
		for (PathElement id : iterpaths->getPath()){
			if (id.getLoF() == RIGHT) {
				string auxstr = to_string(txID) + to_string(id.getId());
				txID = generateIDString(auxstr);
			}
			if (id.getLoF() == LEFT) {
				string auxstr = to_string(id.getId()) + to_string(txID);
				txID = generateIDString(auxstr);
			}

		}
		if (txID != hb.getRoot()->getID()) {

			cout << "no Valida" << endl;
			sleep_for(seconds(60));
			return false;
		}
	}
	cout << endl;
	cout << "Valida" << endl;
	sleep_for(seconds(2));
	return true;
}





