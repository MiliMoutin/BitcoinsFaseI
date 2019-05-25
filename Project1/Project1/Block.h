#pragma once
#include "MerkleRoot.h"
#include "Transaction.h"
#include "HeaderBlock.h"

class Block {
public:
	Block(vector<Transaction> transactions);
	HeaderBlock getHeader() { return HeaderBlock(id, &root); }
	unsigned long getId() { return this->id; }


private:
	MerkleRoot root;
	unsigned long id;
	unsigned long cantTransactions;
	vector<Transaction> transactions;
};