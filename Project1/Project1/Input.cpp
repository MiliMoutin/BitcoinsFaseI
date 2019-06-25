#include "Input.h"

Input::Input(string BlockID, string UTXOId, vector<byte> signature) { 
	this->BlockID = BlockID; 
	this->UTXOId = UTXOId; 
	this->signature = signature; 
}

Input::Input(string BlockID, string UTXOId) {
	this->BlockID = BlockID;
	this->UTXOId = UTXOId;
}

Input::Input(nlohmann::json j) {
	string i= j["BlockID"];
	this->BlockID = i;
	string k = j["UTXOID"];
	this->UTXOId = k;
	/*CAMBIAR TEMA DEL INPUT*/
}

string Input::toSign() {
	return this->getUTXOId();
}

nlohmann::json Input::transformToJson() {

	nlohmann::json j;

	j["BlockID"] = BlockID;
	j["UTXOID"] = UTXOId;
	j["signature"] = this->signature;

	return j;
}