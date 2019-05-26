#pragma once
#include "MerkleBlock.h"

class MerkleRoot{
public:
	MerkleRoot(unsigned long id) { this->id = id; }
	void setId(unsigned long id) { this->id = id; }
	bool setFirstChildren(MerkleBlock* l, MerkleBlock* r) {
		this->left = l; this->right = r;
	}
	MerkleRoot(){}
	MerkleBlock* getLeft() { return this->left; }
	MerkleBlock* getRight() { return this->right; }

private:
	unsigned long id;
	MerkleBlock* left;
	MerkleBlock* right;
};