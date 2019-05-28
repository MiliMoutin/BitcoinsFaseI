#pragma once
#include <vector>
#include "SPV.h"
#include "GenerateID.h"
#include "MerkleNode.h"
#include "MerkleRoot.h"
#include "HeaderBlock.h"
#include "Block.h"

class SPV;

class Full {
public:
	Full(string id);
	virtual string getId() { return this->id; }
	void attach(SPV* n);
	virtual string getType() { return "Full"; }
	void setFilter(string id);
	HeaderBlock askForHeader() { return this->blockchain.back().getHeader(); }
	void injectBlock(Block b);

private:
	//si llega un bloque y aparece alguno de los filters el node avisa
	vector<string> filters;
	list<SPV*> neighbours;
	list<Block> blockchain;
	string id;
	vector<MerkleRoot*> merkleroots;

	int index;

	MerkleNode* createTreeRec(int cantCicle, vector<Transaction> Txsvec);
	MerkleRoot* createTree(Block b);
	bool SearchForFilterTransactions(Block b, string id);
	vector<unsigned long> getPath(MerkleRoot* mr, unsigned long id);
	bool searchPathRec(MerkleNode* n, vector<unsigned long>& path, unsigned long id);
	EDAMerkleBlock getTreeInfo(string id);//devuelve los paths a las transacciones necesarias
	
};
