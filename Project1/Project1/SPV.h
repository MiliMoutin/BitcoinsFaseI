#pragma once
#include "Node.h"
#include "MerkleRoot.h"
#include "EDAMerkleTree.h"
#include "UTXO.h"


class SPV:	public Node {
public:
	virtual void attach();
	virtual string getType();
	virtual string getId();
	virtual void getFilter();

private:
	list <MerkleRoot> headers;
	list <EDAMerkleTree> mtlist;
	list <UTXO> UTXOs;
};