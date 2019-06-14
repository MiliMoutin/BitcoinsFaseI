#pragma once
#include <iostream>
#include "Transaction.h"
#include <list>
#include <vector>
#include "nlohmann/json.hpp"
#include "Path.h"

using namespace std;

class EDAMerkleBlock {
public:
	EDAMerkleBlock(nlohmann::json j);
	EDAMerkleBlock(list<Transaction> transactions, list<Path> paths, list<string> ids, string blockID);
	list<Transaction> getTransactions() { return transactions; }
	list<Path> getPaths() { return paths; }
	Transaction getTransaction(string id);
	string getBlockID() { return this->BlockID; }
	nlohmann::json TransformToJson();


private:
	int cantTransactions;
	string BlockID;
	list<string> transactionIds;
	list<Transaction> transactions;
	list<Path> paths;
	
};
