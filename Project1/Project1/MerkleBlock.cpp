#include "MerkleBlock.h"


MerkleBlock::MerkleBlock(unsigned long id, Transaction t):t() { 
	this->blockId = id; 
	this->t = t; 
}


MerkleBlock::MerkleBlock(unsigned long id):t() { 
	blockId = id; 
	this->lastBlock = false; }