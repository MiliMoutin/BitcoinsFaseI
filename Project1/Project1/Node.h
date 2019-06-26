#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Crypto.h"
#include "/Users/User/source/repos/BitcoinsFaseI2/Project1/cryptopp820/cryptlib.h"
#include "/Users/User/source/repos/BitcoinsFaseI2/Project1/cryptopp820/ecp.h"
#include "/Users/User/source/repos/BitcoinsFaseI2/Project1/cryptopp820/eccrypto.h"
#include "/Users/User/source/repos/BitcoinsFaseI2/Project1/cryptopp820/hex.h"
#include "/Users/User/source/repos/BitcoinsFaseI2/Project1/cryptopp820/oids.h"
#include "/Users/User/source/repos/BitcoinsFaseI2/Project1/cryptopp820/osrng.h"
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
	bool verifyTx(Transaction& t, ECDSA<ECP, SHA256>::PublicKey& pk);
	void visit() { visited = true; }
	ECDSA<ECP, SHA256>::PublicKey getPk();
	string getPublicID() { return this->publicId; }
	bool wasVisited() { return visited; }
	void reset() { visited = false; }
	void set_position(int x, int y) { position.px = x; position.py = y; return; }
	node_pos get_position() { return position; }
	bool operator==(Node* n);
	unsigned long getUTXOId(double amount, string idReceiver, string txid);

protected:

	bool canDoTx(double amount);
	void createPPKey();
	list<UTXO> UTXOs;
	list <Node*> neighbours;
	Transaction to_send;
	bool visited;
	string publicId;
	CryptoPP::ECDSA<ECP, SHA256>::PrivateKey privateKey;
	CryptoPP::ECDSA<ECP, SHA256>::PublicKey publicKey;
	Crypto crypp;
	bool received;

	node_pos position;
};
