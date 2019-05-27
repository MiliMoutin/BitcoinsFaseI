#pragma once
#include "GenerateID.h"
#include "MerkleRoot.h"
#include <vector>
#include "Transaction.h"
#include "HeaderBlock.h"
#include "MerkleNode.h"

class Block {
public:
	Block(){}
	Block(vector<Transaction> transactions, MerkleRoot mr, unsigned long id);
	//devuelve un header con los datos del bloque
	HeaderBlock getHeader() { return HeaderBlock(id, &root); }
	unsigned long getId() { return this->id; }
	MerkleRoot* getRoot() { return &root; }
	//devuelve true si existe una transaccion en el bloque con ese id
	bool isIdPresent(string id);
	unsigned long getCantTxs() { return transactions.size(); }
	Transaction getTransaction(unsigned long id);

	
private:
	MerkleRoot root;
	unsigned long id;
	unsigned long cantTransactions;
	vector<Transaction> transactions;
};