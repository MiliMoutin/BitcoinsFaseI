#pragma once
#include <iostream>
#include "Transaction.h"
#include <list>
#include <vector>

using namespace std;

class EDAMerkleBlock {
public:
	EDAMerkleBlock(list<Transaction> transactions, list<vector<unsigned long>> paths, unsigned long id);
	list<Transaction> getTransactions() { return transactions; }
	list<vector<unsigned long>> getPaths() { return paths; }
	Transaction getTransaction(unsigned long id);
	unsigned long getBlockId() { return this->BlockID; }


private:
	unsigned long BlockID;
	unsigned long int cantTransactions;
	list<unsigned long> transactionIds;
	list<Transaction> transactions;
	list<vector<unsigned long>> paths;
	//unsigned long id;
};
