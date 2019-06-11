#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>


using namespace std;


class Input {
	public:
	Input(){ }
	Input(unsigned long BlockID, unsigned long UTXOId) { this->BlockID = BlockID; this->UTXOId = UTXOId; }
	unsigned long getUTXOId() { return this->UTXOId; }
	unsigned long getBlockID() { return this->BlockID; }
	nlohmann::json transformToJson() { nlohmann::json j; j["BlockID"] = to_string(BlockID); j["UTXOID"] = to_string(UTXOId); return j; }

private:
	unsigned long BlockID;
	unsigned long UTXOId;

};