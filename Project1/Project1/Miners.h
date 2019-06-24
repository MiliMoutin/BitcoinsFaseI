#pragma once
#include "Full.h"
#include "cryptlib.h"
#include "nlohmann/json.hpp"

class Miner : public Full {
public:
	Miner(string id) { this->id = id; }
	Miner() { }
	virtual string getID() { return this->id; }
	virtual string getType() { return "Miner"; }
	virtual void receiveTx(nlohmann::json tx, Node* n);
	void makeTx(string publicId, double EDACoins);
	void startMine();
	void adjustMine(int challenge);
	bool mine();
	void sendBlock();
protected:
	vector<Transaction> toMine;
	int challenge;
};
