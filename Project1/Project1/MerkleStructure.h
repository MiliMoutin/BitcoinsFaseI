#pragma once

class MerkleStructure {
public:
	virtual MerkleStructure* getLeft();
	virtual MerkleStructure* getRight();
	virtual bool isIdPresent(string id);
};

