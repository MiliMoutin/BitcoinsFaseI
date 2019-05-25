#pragma once
#include "MerkleRoot.h"

class HeaderBlock {
public: 
	HeaderBlock(unsigned long id, MerkleRoot* root) { this->id = id; this->root = root; }

private: 
	unsigned long id;
	MerkleRoot* root;
};
