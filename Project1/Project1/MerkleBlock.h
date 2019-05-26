#pragma once
#include "Transaction.h"
#include <vector>

class MerkleBlock {
public:
	MerkleBlock(unsigned long id, Transaction t);
	MerkleBlock(unsigned long id);
	bool isLastBlock() { return lastBlock; }
	bool setLeft(MerkleBlock* l) { return this->left = left; }
	bool setRight(MerkleBlock* r) { return this->right = right; }
	unsigned long getBlockId() { return this->blockId; }
	Transaction getTransaction() { if (lastBlock) { return this->t; } }
	MerkleBlock* getLeft() { return this->left; }
	MerkleBlock* getRight() { return this->right; }

private: 
	Transaction t;
	bool lastBlock;
	unsigned long blockId;
	MerkleBlock* left;
	MerkleBlock* right;
};