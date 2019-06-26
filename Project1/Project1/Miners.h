#pragma once
#include "Full.h"
#include "../cryptopp820/cryptlib.h"
#include "nlohmann/json.hpp"
#define INCREMENT 0x00000001
#define CHALLENGEMASK 0xF0

class Miner : public Full {
public:
	Miner(string id) { this->id = id; Node::createPPKey(); challenge = 1; }
	Miner() { Node::createPPKey(); }
	virtual string getID() { return this->id; }
	virtual string getType() { return "Miner"; }
	virtual void receiveTx(nlohmann::json tx, Node* n);
	void makeTx(string publicId, double EDACoins);
	void startMine();
	void adjustMine();
	bool mine();
	string Challenge();
	void hasMined();

protected:
	int mined;
	vector<Transaction> toMine;
	vector<unsigned long> nounces;
	unsigned int challenge;
	unsigned int newNonce();
	string strToHash(unsigned int& nounce);
	string& MakeStr(MerkleNode* mn, string& str);
	vector<byte> hashed;
	Block lastMined;
	unsigned int winnerNonce;
};
