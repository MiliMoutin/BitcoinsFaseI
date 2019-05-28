#pragma once
#include "Node.h"
#include "EDAMerkleBlock.h"
#include "HeaderBlock.h"
#include "Full.h"
#include "MerkleNode.h"
#include "UTXO.h"

class Full;

class SPV{
public:
	SPV(string id) { this->id = id; }
	void attach(SPV* s);
	void attach(Full* n);
	virtual string getType() { return "SPV"; }
	virtual string getId() { return id; }
	void askForHeader();
	void notify(EDAMerkleBlock mb, HeaderBlock h);
	HeaderBlock getLastHeader() { return this->headers.back(); }

private:
	list <SPV*> neighboursSPV;
	list <Full*> neighboursFull;
	list <HeaderBlock> headers;
	list <MerkleRoot*> roots;
	string id;
	list <UTXO> UTXOs;
	
	bool validNotification(EDAMerkleBlock edamb, HeaderBlock h);
	bool headerPresent(unsigned long headerId);
};