#include "SPV.h"


void SPV::attach(Node* n) {
	this->neighbours.push_back(n);
}

void SPV::notify(HeaderBlock h, EDAMerkleBlock md) {
	this->headers.push_back(h);
	if (validNotification(h, md)) {
		//guardo el header
		this->headers.push_back(h);
		//guardo las UTXOs 
		for (Transaction t : md.getTransactions()) {
			UTXO to_push(t.amountOutput(), t.getUTXOId());
			this->UTXOs.push_back(to_push);
		}
	}

}


bool SPV::validNotification(HeaderBlock h, EDAMerkleBlock md) {
	list<Transaction> transactions = md.getTransactions();
	list<vector<unsigned long>> paths = md.getPaths();

	list<Transaction>::iterator it_t = transactions.begin();
	list<vector<unsigned long>>::iterator it_p = paths.begin();
	
	for (; it_t != transactions.end() || it_p != paths.end(); it_t++, it_p) {
		return wrapper(h.getRoot(), *it_t, *it_p);
	}
	
}


bool SPV::wrapper(MerkleRoot* mr, Transaction t, vector<unsigned long> p) {
	MerkleBlock* left = mr->getLeft();
	MerkleBlock* right = mr->getRight();
	if (left!=nullptr && left->getBlockId()==p[0]) {
		return validNotificationRec(left, t, p, 1);
	}
	if (right!=nullptr && right->getBlockId() == p[0]) {
		return validNotificationRec(right, t, p, 1);
	}
	else return false;
}


bool SPV::validNotificationRec(MerkleBlock* mb, Transaction t, vector<unsigned long> p, int pos) {
	MerkleBlock* left = mb->getLeft();
	MerkleBlock* right = mb->getRight();
	if (mb->isLastBlock()) {
		if (mb->getTransaction().idReceiver() == this->id) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (left->getBlockId() == p[pos]) {
		return validNotificationRec(left, t, p, pos+1);
	}
	else if (right->getBlockId() == p[pos]) {
		return validNotificationRec(right, t, p, pos+1);
	}
	else {
		return false;
	}
}