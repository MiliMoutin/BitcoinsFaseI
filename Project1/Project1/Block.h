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
	
	Block(nlohmann::json jsonBlock);

	Block(vector<Transaction> transactions,string id="AhoraNo", MerkleRoot* mr = nullptr);

	//devuelve un header con los datos del bloque
	HeaderBlock getHeader() { 
		return HeaderBlock(id, root);
	}

	void setRoot(MerkleRoot* mr) { this->root = mr; }

	string getId() { return this->id; }

	MerkleRoot* getRoot() { return root; }

	vector<Transaction> getTxs() { return this->transactions; }

	//devuelve true si existe una transaccion en el bloque con ese id
	bool isIdPresent(string id);

	void setTreeLength(int length) { treeLength = length; }

	unsigned long getCantTxs() { return transactions.size(); }

	Transaction getTransaction(string id);
	 
	nlohmann::json TransformToJson();

	
private:
	int treeLength;
	MerkleRoot* root;
	string id;
	int cantTransactions;
	vector<Transaction> transactions;
};