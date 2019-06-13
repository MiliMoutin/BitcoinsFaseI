#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>


using namespace std;

/*Transaction ID, BlockID, PublicKey, Signature*/

class Input {
	public:
	Input(){ }
	Input(unsigned long BlockID, unsigned long UTXOId, string signature) { this->BlockID = BlockID; this->UTXOId = UTXOId; this->signature = signature; }
	unsigned long getUTXOId() { return this->UTXOId; }
	unsigned long getBlockID() { return this->BlockID; }
	nlohmann::json transformToJson() { nlohmann::json j; 
	j["BlockID"] = to_string(BlockID); 
	j["UTXOID"] = to_string(UTXOId);  
	j["signature"] =this->signature; 
	return j;
	}
	string getSignature() { return this->signature; }

private:
	unsigned long BlockID;
	unsigned long UTXOId;
	string signature;

};