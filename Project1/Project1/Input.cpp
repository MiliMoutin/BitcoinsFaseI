#include "Input.h"

Input::Input(string BlockID, string UTXOId, string signature) { 
	this->BlockID = BlockID; 
	this->UTXOId = UTXOId; 
	this->signature = signature; 
}

Input::Input(nlohmann::json j) {
	string i= j["BlockID"];
	this->BlockID = i;
	string k = j["UTXOID"];
	this->UTXOId = k;
	string m = j["Signature"];
	this->signature = m;
}

nlohmann::json Input::transformToJson() {

	nlohmann::json j;

	j["BlockID"] = BlockID;
	j["UTXOID"] = UTXOId;
	j["signature"] = this->signature;

	return j;
}