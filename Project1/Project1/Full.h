#pragma once
#include <vector>
#include "MerkleRoot.h"
#include "Node.h"
#include "Block.h"

class Full : public Node {
public:
	Full(string id);
	virtual bool attach(Node n);
	virtual string getType() { return this->type; }

private:
	list<Block> blockchain;
	vector<MerkleRoot> merkleroots;
};