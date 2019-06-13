#pragma once
#include "Full.h"

class Miner : public Full {
public:
	Miner(string id) { this->id = id; }
	virtual string getID() { return this->id; }
	virtual string getType() { return "Miner"; }
	virtual void receiveTx(nlohmann::json tx, Node* n);
	void makeTx(string publicId, double EDACoins);

protected:
	vector<Transaction> toMine;

};
