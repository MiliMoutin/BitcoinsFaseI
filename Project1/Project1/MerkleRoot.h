#pragma once
#include "MerkleNode.h"

class MerkleRoot{
public:
	MerkleRoot(){}
	MerkleRoot(unsigned long id) { this->id = id;  left= nullptr; right = nullptr; }
	void setId(unsigned long id) { this->id = id; }
	bool setFirstChildren(MerkleNode* l, MerkleNode* r) {
		if (l != nullptr || r != nullptr) {
			return false;
		}
		else {
			this->left = l; this->right = r;
		}
		return true;
	}
	MerkleNode* getLeft() { return this->left; }
	MerkleNode* getRight() { return this->right; }
	unsigned long getID() { return this->id; }

private:
	unsigned long id;
	MerkleNode* left;
	MerkleNode* right;
};