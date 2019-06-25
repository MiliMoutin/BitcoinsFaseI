#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "Crypto.h"


using namespace std;

/*Transaction ID, BlockID, PublicKey, Signature*/

class Input {
	public:
	Input(){ }
	Input(nlohmann::json j);
	Input(string BlockID, string UTXOId,string publicId="");
	Input(string BlockID, string UTXOId, vector<byte> signature, string publicId="");
	string getBlockID() { return this->BlockID; }
	string getUTXOId() { return this->UTXOId; }
	nlohmann::json transformToJson();
	vector<byte> getSignature() { return this->signature; }
	string toSign();
	string getPublicID() { return this->publicKey; }
	void setSignature(vector<byte> str) { this->signature = str; }

private:
	string BlockID;
	string UTXOId;
	vector<byte> signature;
	string signStr;
	string publicKey;
	Crypto crypp;
};