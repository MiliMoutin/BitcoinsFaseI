#pragma once
#include "GenerateID.h"
#include "MerkleRoot.h"
#include <vector>
#include "Transaction.h"
#include "HeaderBlock.h"
#include "MerkleNode.h"
#include "Subject.h"

class Block :public Subject{
public:
	Block(){}

	Block(vector<Transaction> transactions, unsigned long id, MerkleRoot* mr = nullptr);

	//devuelve un header con los datos del bloque
	HeaderBlock getHeader() { 
		return HeaderBlock(id, root);
	}

	void setRoot(MerkleRoot* mr) { this->root = mr; }

	unsigned long getId() { return this->id; }

	MerkleRoot* getRoot() { return root; }

	vector<Transaction> getTxs() { return this->transactions; }

	//devuelve true si existe una transaccion en el bloque con ese id
	bool isIdPresent(string id);

	void setTreeLength(int length) { treeLength = length; }

	unsigned long getCantTxs() { return transactions.size(); }

	Transaction getTransaction(unsigned long id);

	
private:
	int treeLength;
	MerkleRoot* root;
	unsigned long id;
	unsigned long cantTransactions;
	vector<Transaction> transactions;
};