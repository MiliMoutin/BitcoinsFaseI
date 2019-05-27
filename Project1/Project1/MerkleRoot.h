#pragma once
#include "MerkleNode.h"

class MerkleRoot{
public:
	MerkleRoot(unsigned long id) { this->id = id; }
	void setId(unsigned long id) { this->id = id; }
	bool setFirstChildren(MerkleNode* l, MerkleNode* r) {
		this->left = l; this->right = r;
	}
	MerkleRoot(){}
	MerkleNode* getLeft() { return this->left; }
	MerkleNode* getRight() { return this->right; }

private:
	unsigned long id;
	MerkleNode* left;
	MerkleNode* right;
};