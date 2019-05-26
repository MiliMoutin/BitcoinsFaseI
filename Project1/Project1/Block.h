#pragma once
#include "GenerateID.h"
#include "MerkleRoot.h"
#include <vector>
#include "Transaction.h"
#include "HeaderBlock.h"
#include "MerkleNode.h"

class Block {
public:
	Block(vector<Transaction> transactions);
	HeaderBlock getHeader() { return HeaderBlock(id, &root); }
	unsigned long getId() { return this->id; }
	MerkleRoot* getRoot() { return &root; }
	bool isIdPresent(string id);
	Transaction getTransaction(unsigned long id);

	
private:
	MerkleRoot root;
	unsigned long id;
	unsigned long cantTransactions;
	vector<Transaction> transactions;
};