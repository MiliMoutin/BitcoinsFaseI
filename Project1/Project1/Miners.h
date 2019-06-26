#pragma once
#include "Full.h"
#include "../cryptopp820/cryptlib.h"
#include "nlohmann/json.hpp"
#define INCREMENT 0x00000001
#define CHALLENGEMASK 0xF0

class Miner : public Full {
public:
	Miner(string id):started(false) { this->id = id; Node::createPPKey(); challenge = 1; }
	Miner() { Node::createPPKey(); }
	virtual string getID() { return this->id; }
	virtual string getType() { return "Miner"; }
	virtual void receiveTx(nlohmann::json tx, Node* n, ECDSA<ECP, SHA256>::PublicKey& pk);
	void makeTx(string publicId, double EDACoins);
	void startMine();
	void adjustMine(double start, double end);
	bool mine();
	string Challenge();
	void hasMined();

protected:
	int mined;
	bool started;
	vector<Transaction> toMine;
	unsigned int challenge;
	unsigned int newNonce();
	string strToHash(unsigned int& nounce);
	string hashed;

	Block lastMined;
	unsigned int winnerNonce;
	Transaction createWinnerTransaction();
};
