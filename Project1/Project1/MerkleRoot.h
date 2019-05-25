#pragma once
#include "MerkleBlock.h"

class MerkleRoot {


private:
	MerkleBlock* left;
	MerkleBlock* right;
};