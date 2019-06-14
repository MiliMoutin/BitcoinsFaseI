
#pragma once
#include "Transaction.h"
#include <vector>

class MerkleNode {
public:
	MerkleNode(MerkleNode* l = nullptr, MerkleNode* r = nullptr) { this->left = l; this->right = r; }
	MerkleNode(unsigned long id, MerkleNode* l=nullptr, MerkleNode* r=nullptr) { this->blockId = id; this->left = l; this->right = r; }
	bool isLastBlock() { return left==nullptr && right==nullptr; }
	void setLeft(MerkleNode* l) {  this->left = l; }
	void setRight(MerkleNode* r) {  this->right = r; }
	string getBlockId() { return this->blockId; }
	MerkleNode* getLeft() { return this->left; }
	MerkleNode* getRight() { return this->right; }
	void setId(string id) { this->blockId = id; }

private: 
	string blockId;
	MerkleNode* left;
	MerkleNode* right;
};