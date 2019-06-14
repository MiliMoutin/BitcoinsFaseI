#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>


using namespace std;

/*Transaction ID, BlockID, PublicKey, Signature*/

class Input {
	public:
	Input(){ }
	Input(nlohmann::json j);
	Input(string BlockID, string UTXOId, string signature);
	string getBlockID() { return this->BlockID; }
	string getUTXOId() { return this->UTXOId; }
	nlohmann::json transformToJson();
	string getSignature() { return this->signature; }

private:
	string BlockID;
	string UTXOId;
	string signature;

};