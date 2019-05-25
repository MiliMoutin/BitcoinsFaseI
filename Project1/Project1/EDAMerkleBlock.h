#pragma once
#include <iostream>
#include "Transaction.h"
#include <list>
#include <vector>

using namespace std;

class EDAMerkleBlock {
public:
	EDAMerkleBlock(list<Transaction> transactions, list<vector<unsigned long>> paths) {
		this->transactions = transactions;
		this->paths = paths;
		this->cantTransactions = cantTransactions;
	}

private:
	unsigned long int cantTransactions;
	list<unsigned long> transactionIds;
	list<Transaction> transactions;
	list<vector<unsigned long>> paths;
	unsigned long id;
};