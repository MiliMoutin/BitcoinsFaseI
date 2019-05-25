#pragma once
#include "Transaction.h"

class MerkleBlock {


private: 
	unsigned long cantTransactions;
	list<unsigned long> id;
	list<Transaction> transactions;
	list<unsigned long> mplong;
	//list<MerklePath>
	MerkleBlock* left;
	MerkleBlock* right;
};