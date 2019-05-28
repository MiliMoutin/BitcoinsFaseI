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
	for (Full* f : this->neighboursFull) {
		HeaderBlock header = f->askForHeader();
		if (!headerPresent(header.getBlockId())) {
			this->headers.push_back(header);
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

void SPV::notify(EDAMerkleBlock md) {
	//busco a que header corresponde el bloque que llego
	HeaderBlock h;
	for (HeaderBlock hd : this->headers) {
		if (md.getBlockID() == hd.getBlockId()) {
			h = hd;
		}

	}
	//espero 10 min
	h = this->getLastHeader();
	
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
	list<vector<unsigned long>> paths = edamb.getPaths();
	list<Transaction> transactions = edamb.getTransactions();

	list<vector<unsigned long>>::iterator iterpaths;
	list<Transaction>::iterator itertxs;

	for (iterpaths = paths.begin(), itertxs = transactions.begin(); iterpaths != paths.end(); iterpaths++, itertxs++) {
		unsigned long txID = itertxs->getId();
		//iter los ids y genero el id final
		for (unsigned long id : *iterpaths) {
			unsigned char* auxchar;
			string auxstr = to_string(txID) + to_string(id);
			auxchar = (unsigned char *)auxstr.c_str();
			txID = generateID(auxchar);
		}
		if (txID != hb.getRoot()->getID()) {
			return false;
		}
		
	}
	return true;
}





