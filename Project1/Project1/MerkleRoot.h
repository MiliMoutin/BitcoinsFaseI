#pragma once
#include "MerkleBlock.h"

class MerkleRoot{
public:
	bool setFirstChildren(MerkleBlock* l, MerkleBlock* r);
	MerkleBlock* getLeft() { return this->left; }
	MerkleBlock* getRight() { return this->right; }

private:
	MerkleBlock* left;
	MerkleBlock* right;
};