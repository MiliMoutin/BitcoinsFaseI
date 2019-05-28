#include "EDAMerkleBlock.h"

EDAMerkleBlock::EDAMerkleBlock(list<Transaction> transactions, list<vector<unsigned long>> paths, list<unsigned long> ids, unsigned long BlockID) {
	this->transactions = transactions;
	this->transactionIds = ids;
	this->paths = paths;
	this->cantTransactions = transactions.size();
	this->BlockID = BlockID;
}

Transaction EDAMerkleBlock::getTransaction(unsigned long id) {
	for (Transaction t : transactions) {
		if (t.getId() == id) {
			return t;
		}
	}
}