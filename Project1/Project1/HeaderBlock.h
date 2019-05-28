#pragma once
#include "MerkleRoot.h"

class HeaderBlock {
public: 
	HeaderBlock(unsigned long id, MerkleRoot* root) { this->id = id; this->root = root; }
	HeaderBlock() {}
	MerkleRoot* getRoot() { return root; }
	unsigned long getBlockId() { return id; }

private: 
	unsigned long id;
	MerkleRoot* root;
};
