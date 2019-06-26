#include "MerkleNode.h"

MerkleNode::MerkleNode(nlohmann::json j) {
	if (j[LAST] == true) {
		this->setId(j[ID]);
	}
	else {
		this->setId(j[ID]);
		this->left = MerkleNodeRec(j[NODES][0]);
		this->right = MerkleNodeRec(j[NODES][1]);
	}
}

MerkleNode* MerkleNode::MerkleNodeRec(nlohmann::json j) {
	if (j[LAST] == true) {
		MerkleNode* mn = new MerkleNode();
		mn->setId(j[ID]);
		return mn;
	}
	else {
		MerkleNode* l = MerkleNodeRec(j[NODES][0]);
		MerkleNode* r = MerkleNodeRec(j[NODES][1]);
		return new MerkleNode(j[ID], l, r);
	}

}

