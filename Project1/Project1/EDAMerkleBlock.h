#pragma once
#include <iostream>
#include "Transaction.h"
#include <list>
#include <vector>

using namespace std;

class EDAMerkleBlock {
public:
	EDAMerkleBlock(list<Transaction> transactions, list<vector<unsigned long>> paths);
	list<Transaction> getTransactions() { return transactions; }
	list<vector<unsigned long>> getPaths() { return paths; }
	Transaction getTransaction(unsigned long id);


private:
	unsigned long int cantTransactions;
	list<unsigned long> transactionIds;
	list<Transaction> transactions;
	list<vector<unsigned long>> paths;
	//unsigned long id;
};
