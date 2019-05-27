#include "EDAMerkleBlock.h"

EDAMerkleBlock::EDAMerkleBlock(list<Transaction> transactions, list<vector<unsigned long>> paths, unsigned long id) {
	this->transactions = transactions;
	this->BlockID = id;
	this->paths = paths;
	this->cantTransactions = transactions.size();
}

Transaction EDAMerkleBlock::getTransaction(unsigned long id) {
	for (Transaction t : transactions) {
		if (t.getId() == id) {
			return t;
		}
	}
}