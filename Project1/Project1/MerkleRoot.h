#pragma once
#include "MerkleNode.h"

class MerkleRoot{
public:
	MerkleRoot(){}
	MerkleRoot(nlohmann::json jsonTree);
	MerkleRoot(string id) { this->id = id;  left= nullptr; right = nullptr; }
	void setId(string id) { this->id = id; }
	void setFirstChildren(MerkleNode* l, MerkleNode* r) {
			this->left = l; this->right = r;
	}
	MerkleNode* getLeft() { return this->left; }
	MerkleNode* getRight() { return this->right; }
	string getID() { return this->id; }
	nlohmann::json TransformToJson();


private:
	string id;
	MerkleNode* left;
	MerkleNode* right;
	nlohmann::json BuiltJsonTree(MerkleNode* n);
	MerkleNode* BuiltTreefromJson(nlohmann::json j);
};