#pragma once
#include <iostream>
#include "Transaction.h"
#include <list>
#include <vector>
#include "Path.h"

using namespace std;

class EDAMerkleBlock {
public:
	EDAMerkleBlock(list<Transaction> transactions, list<Path> paths, list<unsigned long> ids, unsigned long blockID);
	list<Transaction> getTransactions() { return transactions; }
	list<Path> getPaths() { return paths; }
	Transaction getTransaction(unsigned long id);
	unsigned long getBlockID() { return this->BlockID; }


private:
	int cantTransactions;
	unsigned long BlockID;
	list<unsigned long> transactionIds;
	list<Transaction> transactions;
	list<Path> paths;
	
};
