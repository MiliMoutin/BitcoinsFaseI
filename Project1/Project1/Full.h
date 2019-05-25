#pragma once
#include <vector>
#include "MerkleRoot.h"
#include "HeaderBlock.h"
#include "Node.h"
#include "Block.h"

class Full : public Node {
public:
	Full(string id);
	virtual bool attach(Node n);
	virtual string getType() { return this->type; }
	HeaderBlock sendHeader();
	MerkleRoot sendRoot();
	void setFilter(string id);

private:
	vector<string> filters;
	string id;
	string type;
	list<Block> blockchain;
	vector<MerkleRoot> merkleroots;
};