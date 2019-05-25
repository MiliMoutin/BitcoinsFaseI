#pragma once
#include "Transaction.h"
#include <vector>

class MerkleBlock :public MerkleStructure {
public:
	MerkleBlock(unsigned long id, Transaction t) { blockId = id; this->t = t; }
	MerkleBlock(unsigned long id) { blockId = id; this->lastBlock = false; }
	bool isLastBlock() { return lastBlock; }
	bool setLeft(MerkleBlock* l) { this->left = left; }
	Transaction getTransaction() { if (lastBlock) { return this->t; } }
	bool setRight(MerkleBlock* r) { this->right = right; }
	unsigned long getBlockId() { this->blockId; }
	MerkleBlock* getLeft() { return this->left; }
	MerkleBlock* getRight() { return this->right; }

private: 
	Transaction t;
	bool lastBlock;
	unsigned long blockId;
	MerkleBlock* left;
	MerkleBlock* right;
};