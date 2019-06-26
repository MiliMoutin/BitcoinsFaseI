#pragma once
#include "Transaction.h"
#include <vector>
#define ID "id"
#define LAST "last"
#define NODES "nodes"

class MerkleNode {
public:
	MerkleNode(MerkleNode* l = nullptr, MerkleNode* r = nullptr) { this->left = l; this->right = r; }
	MerkleNode(string id, MerkleNode* l=nullptr, MerkleNode* r=nullptr) { this->blockId = id; this->left = l; this->right = r; }
	bool isLastBlock() { return left==nullptr && right==nullptr; }
	MerkleNode(nlohmann::json j);
	void setLeft(MerkleNode* l) {  this->left = l; }
	void setRight(MerkleNode* r) {  this->right = r; }
	string getBlockId() { return this->blockId; }
	MerkleNode* getLeft() { return this->left; }
	MerkleNode* getRight() { return this->right; }
	void setId(string id) { this->blockId = id; }

private: 
	MerkleNode* MerkleNodeRec(nlohmann::json j);
	string blockId;
	MerkleNode* left;
	MerkleNode* right;
};