#pragma once
#include <iostream>
#include <string>


using namespace std;


class Input {
	public:
	Input(){ }
	Input(unsigned long BlockID, unsigned long UTXOId) { this->BlockID = BlockID; this->UTXOId = UTXOId; }
	unsigned long getUTXOId() { return this->UTXOId; }
	unsigned long getBlockID() { return this->BlockID; }

private:
	unsigned long BlockID;
	unsigned long UTXOId;

};