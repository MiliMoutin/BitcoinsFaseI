#pragma once
#include "Node.h"
#include "EDAMerkleBlock.h"
#include "HeaderBlock.h"
#include "Full.h"
#include "MerkleNode.h"
#include "UTXO.h"

class Full;

class SPV : public Node{

public:
	SPV(string id) { this->id = id; }
	virtual string getType() { return "SPV"; }
	virtual string getID() { return this->id; }
	virtual void attach(Node* n);
	void askForHeader();
	void notify(EDAMerkleBlock mb, HeaderBlock h);
	HeaderBlock getLastHeader() { return this->headers.back(); }

private:
	list <Node*> neighbours;
	list <HeaderBlock> headers;
	list <MerkleRoot*> roots;
	string id;
	list <UTXO> UTXOs;
	
	bool validNotification(EDAMerkleBlock edamb, HeaderBlock h);
	bool headerPresent(unsigned long headerId);
};