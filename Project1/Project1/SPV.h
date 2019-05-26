#pragma once
#include "Node.h"
#include "EDAMerkleBlock.h"
#include "HeaderBlock.h"
#include "MerkleNode.h"
#include "UTXO.h"


class SPV:	public Node {
public:
	SPV(string id) { this->id = id; }
	virtual void attach(Node* n);
	virtual string getType() { return "SPV"; }
	virtual string getId() { return id; }
	void notify(HeaderBlock hd, EDAMerkleBlock mb);

private:
	list <Node*> neighbours;
	list <HeaderBlock> headers;
	list <MerkleRoot*> roots;
	list <UTXO> UTXOs;
	string id;

	bool validNotification(HeaderBlock hd, EDAMerkleBlock md);
	bool wrapper(MerkleRoot* mr, Transaction t, vector<unsigned long> p, EDAMerkleBlock emb);
	bool validNotificationRec(MerkleNode* mb, Transaction t, vector<unsigned long> p, int pos, EDAMerkleBlock emb);
};