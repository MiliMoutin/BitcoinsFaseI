#pragma once
#include "MerkleRoot.h"

class HeaderBlock {
public: 
	HeaderBlock(string id, MerkleRoot* root) { this->id = id; this->root = root; }
	HeaderBlock() {}
	HeaderBlock(nlohmann::json jh) {
		string i= jh["BlockID"];
		this->id = i;
		this->root = new MerkleRoot(jh["MerkleRoot"]);
	}
	HeaderBlock(MerkleRoot* root) { this->root = root; }
	nlohmann::json TransformToJson() {
		nlohmann::json j;
		j["BlockID"] = this->id;
		j["root"] = this->root->TransformToJson();
		return j;
	}
	MerkleRoot* getRoot() { return root; }
	string getBlockId() { return id; }

private: 
	string id;
	MerkleRoot* root;
};
