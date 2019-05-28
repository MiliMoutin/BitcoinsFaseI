#include "EDAMerkleBlock.h"

EDAMerkleBlock::EDAMerkleBlock(list<Transaction> transactions, list<Path> paths, list<unsigned long> ids, unsigned long blockID) {
	this->transactions = transactions;
	this->paths = paths;
	this->transactionIds = ids;
	this->BlockID = BlockID;
	this->cantTransactions = transactions.size();

}

Transaction EDAMerkleBlock::getTransaction(unsigned long id) {
	for (Transaction t : this->transactions) {
		if (t.getId() == id) {
			return t;
		}
	}
}