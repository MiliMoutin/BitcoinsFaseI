#pragma once
#include <vector>
#include "SPV.h"
#include "MerkleNode.h"
#include "MerkleRoot.h"
#include "HeaderBlock.h"
#include "Node.h"
#include "Block.h"

class Full : public Node {
public:
	Full(string id);
	virtual void attach(SPV* n);
	virtual string getType() { return this->type; }
	void setFilter(string id);
	void injectBlock(Block b);

private:
	//si llega un bloque y aparece alguno de los filters el node avisa
	vector<string> filters;
	list<SPV*> neighbours;
	string id;
	string type;
	list<Block> blockchain;
	vector<MerkleRoot*> merkleroots;

	bool SearchForFilterTransactions(Block b, string id);
	EDAMerkleBlock getTreeInfo(Block b, string id);//devuelve los paths a las transacciones necesarias
	void getTreeInfoRec(Block b, MerkleNode* mb, string id, vector<unsigned long> path, list<vector<unsigned long>>* paths, list<Transaction>* transactions);
};
