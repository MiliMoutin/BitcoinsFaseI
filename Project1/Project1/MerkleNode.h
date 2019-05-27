
#pragma once
#include "Transaction.h"
#include <vector>

class MerkleNode {
public:

	MerkleNode(unsigned long id);
	bool isLastBlock() { return left==nullptr && right==nullptr; }
	bool setLeft(MerkleNode* l) { return this->left = left; }
	bool setRight(MerkleNode* r) { return this->right = right; }
	unsigned long getBlockId() { return this->blockId; }
	MerkleNode* getLeft() { return this->left; }
	MerkleNode* getRight() { return this->right; }

private: 
	unsigned long blockId;
	MerkleNode* left;
	MerkleNode* right;
};