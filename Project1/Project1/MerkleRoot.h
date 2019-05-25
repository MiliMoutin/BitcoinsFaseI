#pragma once
#include "MerkleStructure.h"
#include "MerkleBlock.h"

class MerkleRoot: MerkleStructure {
public:
	bool setFirstChildren(MerkleBlock* l, MerkleBlock* r);
	MerkleBlock* getLeft() { this->left; }
	MerkleBlock* getRight() { this->right; }

private:
	MerkleBlock* left;
	MerkleBlock* right;
};