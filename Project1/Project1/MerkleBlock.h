#pragma once
#include "Transaction.h"
#include <vector>

class MerkleBlock {
public:
	MerkleBlock(unsigned long id, vector<Transaction> transactions, vector<unsigned long>idvector);
	bool setLeft(MerkleBlock* l);
	bool setRight(MerkleBlock* r);

private: 
	unsigned long blockId;
	unsigned long cantTransactions;
	list<unsigned long> idvector;
	list<Transaction> transactions;
	list<unsigned long> mplong;
	list<unsigned long> id;
	MerkleBlock* left;
	MerkleBlock* right;
};