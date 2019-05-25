#pragma once
#include "Transaction.h"
#include <vector>

class MerkleBlock :public MerkleStructure {
public:
	MerkleBlock(unsigned long id, vector<Transaction> transactions, vector<unsigned long>idvector);
	bool setLeft(MerkleBlock* l) { this->left = left; }
	bool setRight(MerkleBlock* r) { this->right = right; }
	unsigned long getBlockId() { this->blockId; }
	MerkleBlock* getLeft() { return this->left; }
	MerkleBlock* getRight() { return this->right; }
	bool isIdPresent(string id) {
		for (Transaction* t : transactions)
		{
			if (t->idReceiver() == id) { return true; }
		}
	}

private: 
	unsigned long blockId;
	list<unsigned long> idvector;
	list<Transaction*> transactions;
	list<unsigned long> id;
	MerkleBlock* left;
	MerkleBlock* right;
};