#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Crypto.h"
#include "../cryptopp820/cryptlib.h"
#include "../cryptopp820/ecp.h"
#include "../cryptopp820/eccrypto.h"
#include "../cryptopp820/hex.h"
#include "../cryptopp820/oids.h"
#include "../cryptopp820/osrng.h"
#include "Transaction.h"
#include "nlohmann/json.hpp"
#include "Subject.h"
#include "UTXO.h"

using namespace std;

struct node_pos
{
	int px;
	int py;
};


class Node :public Subject{
public:
	virtual bool isNeighbour(string id) = 0;
	virtual string getType() = 0;
	virtual string getID() = 0;
	virtual void attach(Node* n) = 0;
	virtual list<Node*> getNeighbours() = 0;
	virtual void makeTx(string publicId, double EDACoins);
	Transaction& signTx(Transaction& t);
	bool verifyTx(Transaction& t, string publicID);
	void visit() { visited = true; }
	string getPublicID() { return this->publicId; }
	bool wasVisited() { return visited; }
	void reset() { visited = false; }
	void set_position(int x, int y) { position.px = x; position.py = y; return; }
	node_pos get_position() { return position; }
	bool operator==(Node* n);

protected:
	bool canDoTx(double amount);
	void createPPKey();
	list<UTXO> UTXOs;
	list <Node*> neighbours;
	Transaction to_send;
	bool visited;
	node_pos position;
	string publicId;
	CryptoPP::ECDSA<ECP, SHA256>::PrivateKey privateKey;
	CryptoPP::ECDSA<ECP, SHA256>::PublicKey publicKey;
	Crypto crypp;
};
