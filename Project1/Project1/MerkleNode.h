
#pragma once
#include "Transaction.h"
#include <vector>

class MerkleNode {
public:
	MerkleNode(MerkleNode* l = nullptr, MerkleNode* r = nullptr) { this->left = l; this->right = r; }
	MerkleNode(unsigned long id, MerkleNode* l = nullptr, MerkleNode* r = nullptr) { this->blockId = id; this->left = l; this->right = r; }
	bool isLastBlock() { return left==nullptr && right==nullptr; }
	bool setLeft(MerkleNode* l) { return this->left = left; }
	bool setRight(MerkleNode* r) { return this->right = right; }
	unsigned long getBlockId() { return this->blockId; }
	MerkleNode* getLeft() { return this->left; }
	MerkleNode* getRight() { return this->right; }
	void setId(unsigned long id) { this->blockId = id; }

private: 
	unsigned long blockId;
	MerkleNode* left;
	MerkleNode* right;
};