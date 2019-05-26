#include "EDAMerkleBlock.h"

EDAMerkleBlock::EDAMerkleBlock(list<Transaction> transactions, list<vector<unsigned long>> paths) {
	this->transactions = transactions;
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