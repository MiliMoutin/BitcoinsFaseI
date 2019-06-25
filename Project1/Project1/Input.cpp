#include "Input.h"
#include <iostream>

using namespace std;

Input::Input(string BlockID, string UTXOId, vector<byte> signature, string publicId="") { 
	this->BlockID = BlockID; 
	this->UTXOId = UTXOId; 
	this->signature = signature; 
	this->publicKey = publicId;
}

Input::Input(string BlockID, string UTXOId, string publicId) {
	this->BlockID = BlockID;
	this->UTXOId = UTXOId;
	this->publicKey = publicId;
}

Input::Input(nlohmann::json j) {
	string i= j["BlockID"];
	this->BlockID = i;
	string k = j["UTXOID"];
	this->UTXOId = k;
	vector<byte> sig;
	string str = j["signature"];
	std::stringstream aux;
	for (int i = 0; i < str.size(); i+=2) {
		byte b;
		aux << str[i] + str[i + 1];
		aux >> std::hex >> b;
		sig.push_back(b);
	}
	this->signature = sig;
	string pk = j["PublicKey"];
	this->publicKey = pk;
}

string Input::toSign() {
	return this->getUTXOId();
}

nlohmann::json Input::transformToJson() {

	nlohmann::json j;

	j["BlockID"] = BlockID;
	j["UTXOID"] = UTXOId;
	j["signature"]=crypp.hexPrint(this->signature);
	j["PublicKey"] = this->publicKey;
	return j;

}