#pragma once
#include <vector>
#include "SPV.h"
#include "MerkleNode.h"
#include "MerkleRoot.h"
#include "HeaderBlock.h"
#include "Node.h"
#include "Block.h"

class Full :public Node{
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
	vector<MerkleRoot*> merkleroots;

	bool SearchForFilterTransactions(Block b, string id);
	EDAMerkleBlock getTreeInfo(Block b, string id);//devuelve los paths a las transacciones necesarias
	void getTreeInfoRec(Block b, MerkleNode* mb, string id, vector<unsigned long> path, list<vector<unsigned long>>* paths, list<Transaction>* transactions);
};
