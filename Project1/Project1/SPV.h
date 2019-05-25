#pragma once
#include "Node.h"
#include "EDAMerkleBlock.h"
#include "MerkleStructure.h"
#include "HeaderBlock.h"
#include "MerkleBlock.h"
#include "UTXO.h"


class SPV:	public Node {
public:
	virtual void attach();
	virtual string getType();
	virtual string getId();
	void notify(HeaderBlock hd, EDAMerkleBlock mb);

private:
	list <Node*> neighbours;
	list <HeaderBlock> headers;
	list <MerkleRoot*> mtlist;
	list <UTXO> UTXOs;

};