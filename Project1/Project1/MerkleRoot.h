#pragma once
#include "MerkleBlock.h"

class MerkleRoot {
	bool setFirstChildren(MerkleBlock* l, MerkleBlock* r);

private:
	MerkleBlock* left;
	MerkleBlock* right;
};