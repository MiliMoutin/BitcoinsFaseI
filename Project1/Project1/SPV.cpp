#include "SPV.h"
#include <chrono>
#include <thread>

using namespace std::this_thread; 
using namespace std::chrono; 

void SPV::attach(Node* n) {
	this->neighbours.push_back(n);
}

void SPV::askForHeader() {
	//le pedi a los vecinos FULL que me pasen el header cada 10 min
}

void SPV::notify(EDAMerkleBlock md) {
	//busco a que header corresponde el bloque que llego
	HeaderBlock h;
	for (HeaderBlock hd : this->headers) {
		if (md.getBlockId() == hd.getBlockId()) {
			h = hd;
		}

	}

	sleep_for(minutes(10));
	h = this->getLastHeader();
	
		if (validNotification(h, md)) {
			//guardo las UTXOs 
			for (Transaction t : md.getTransactions()) {
				UTXO to_push(t.amountOutput(), t.getUTXOId());
				this->UTXOs.push_back(to_push);
				this->roots.push_back(h.getRoot());
			}
		}

	}



bool SPV::validNotification(HeaderBlock h, EDAMerkleBlock md) {
	list<Transaction> transactions = md.getTransactions();
	list<vector<unsigned long>> paths = md.getPaths();

	list<Transaction>::iterator it_t = transactions.begin();
	list<vector<unsigned long>>::iterator it_p = paths.begin();
	
	//validation tiene el valor de lo que devuelve wrapper 
	//si wrapper devuelve false, corta y devuelve false
	bool validation = true;
	for (; it_t != transactions.end() || it_p != paths.end() || !validation; it_t++, it_p) {
		validation= wrapper(h.getRoot(), *it_t, *it_p, md);
	}

	return validation;
	
}


bool SPV::wrapper(MerkleRoot* mr, Transaction t, vector<unsigned long> p, EDAMerkleBlock emb){
	MerkleNode* left = mr->getLeft();
	MerkleNode* right = mr->getRight();

	//me fijo porque camino tengo que seguir y si el camino no es valido, devuelvo false
	if (left!=nullptr && left->getBlockId()==p[0]) {
		return validNotificationRec(left, t, p, 1, emb);
	}
	if (right!=nullptr && right->getBlockId()==p[0]) {
		return validNotificationRec(right, t, p, 1, emb);
	}
	else {
		return false;
	}
}


bool SPV::validNotificationRec(MerkleNode* mb, Transaction t, vector<unsigned long> p, int pos, EDAMerkleBlock emb) {
	//si es una hoja, chequeo el block id y no llamo mas
	if (mb->isLastBlock()) {
		if (t.getId()==mb->getBlockId()) {
			return true;
		}
		else {
			return false;
		}
	}
	//si no es una hoja, sigo por el camino, si es que lo hay
	else {
		MerkleNode* left = mb->getLeft();
		MerkleNode* right = mb->getRight();
		if (p.size() >= pos) {
			return false;
		}
		else if (left!=nullptr && left->getBlockId() == p[pos]) {
			return validNotificationRec(left, t, p, pos + 1, emb);
		}
		else if (right!=nullptr && right->getBlockId() == p[pos]) {
			return validNotificationRec(right, t, p, pos + 1, emb);
		}
		else {
		return false;
		}
	}
}