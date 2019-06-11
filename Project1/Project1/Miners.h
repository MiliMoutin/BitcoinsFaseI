#pragma once
#include "Full.h"

class Miner : public Full {
public:
	Miner(string id) { this->id = id; }
	virtual string getID() { return this->id; }
	virtual void attach(Node* n);
	virtual string getType() { return "Miner"; }
	bool isNeighbour(string id);

protected:
	string id;
	vector<string> filters;
	list<Node*> neighbours;
	list<Block> blockchain;
	string id;
	vector<MerkleRoot*> merkleroots;
};