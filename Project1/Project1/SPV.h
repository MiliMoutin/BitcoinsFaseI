#pragma once
#include "Node.h"
#include "HeaderBlock.h"
#include "MerkleBlock.h"
#include "UTXO.h"


class SPV:	public Node {
public:
	virtual void attach();
	virtual string getType();
	virtual string getId();
	virtual void getFilter();

private:
	list <HeaderBlock> headers;
	list <MerkleBlock> mtlist;
	list <UTXO> UTXOs;
};