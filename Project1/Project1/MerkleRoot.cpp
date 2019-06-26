#include "MerkleRoot.h"


MerkleRoot::MerkleRoot(nlohmann::json jsonTree) {
	string i = jsonTree[ID];
	this->id = i;
	if (jsonTree[LAST]==false) {
		left = BuiltTreefromJson(jsonTree[NODES][0]);
		right = BuiltTreefromJson(jsonTree[NODES][1]);
	}
	else {
		left = right = nullptr;
	}
}

MerkleNode* MerkleRoot::BuiltTreefromJson(nlohmann::json tree) {
	if (tree[LAST] == true) {
		string id = tree[ID];
		return new MerkleNode(id);
	}
	else {
		MerkleNode* n = new MerkleNode(tree[ID]);
		n->setLeft(BuiltTreefromJson(tree[NODES][0]));
		n->setRight(BuiltTreefromJson(tree[NODES][1]));
		return n;
	}
}


nlohmann::json MerkleRoot::TransformToJson() {
	nlohmann::json jsonTree;
	jsonTree[ID] = this->id;
	if (this->left == nullptr || this->right == nullptr) {
		jsonTree[LAST] = true;
		jsonTree[NODES] = "vacio";
	}
	else {
		jsonTree[LAST] = false;
		jsonTree[NODES][0] = BuiltJsonTree(left);
		jsonTree[NODES][1] = BuiltJsonTree(right);
	}
	return jsonTree;
}




nlohmann::json MerkleRoot::BuiltJsonTree(MerkleNode* n) {
	if (n->isLastBlock()) {
		nlohmann::json leaf;
		leaf[ID] = n->getBlockId();
		leaf[LAST] = true;
		leaf[NODES] = "vacio";
		return leaf;
	}
	else {
		nlohmann::json node;
		node[ID] = n->getBlockId();
		node[LAST] = false;
		node[NODES][0] = BuiltJsonTree(n->getLeft());
		node[NODES][1] = BuiltJsonTree(n->getRight());
	}
}

