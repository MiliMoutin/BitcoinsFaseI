#pragma once
#include <vector>
#include "SPV.h"
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
	vector<string> filters;
	list<SPV*> neighbours;
	string id;
	string type;
	list<Block> blockchain;
	vector<MerkleRoot*> merkleroots;

	bool SearchForFilterTransactions(Block b, string id);
	EDAMerkleBlock getTreeInfo(Block b, string id);//devuelve los paths a las transacciones necesarias
	void getTreeInfoRec(MerkleBlock* mb, string id, vector<unsigned long> path, list<vector<unsigned long>>* paths, list<Transaction>* transactions);
};
