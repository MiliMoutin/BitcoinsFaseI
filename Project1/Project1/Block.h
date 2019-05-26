#pragma once
#include "GenerateID.h"
#include "MerkleRoot.h"
#include "Transaction.h"
#include "HeaderBlock.h"
#include "MerkleBlock.h"

class Block {
public:
	Block(vector<Transaction> transactions) { this->transactions = transactions; }
	HeaderBlock getHeader() { return HeaderBlock(id, &root); }
	unsigned long getId() { return this->id; }
	MerkleRoot* getRoot() { return &root; }
	bool isIdPresent(string id) {
		for (Transaction t : transactions)
		{
			if (t.idReceiver() == id) { return true; }
		}
	}
	
private:
	MerkleRoot root;
	unsigned long id;
	unsigned long cantTransactions;
	vector<Transaction> transactions;
};