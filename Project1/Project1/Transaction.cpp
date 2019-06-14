#include "Transaction.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

Transaction::Transaction(vector<Input> input, vector<Output> output){
	this->input = input;
	this->output = output;
}


Transaction::Transaction(nlohmann::json j) {
	int i = 0;
	for (nlohmann::json ji : j["input"]) {
		this->input.push_back(Input(j["input"][i]));
		i++;
	}
	i = 0;
	for (nlohmann::json jo : j["output"]) {
		this->output.push_back(Output(j["output"][i]));
	}
}

bool Transaction::isIDPresent(string id) {
	for (Output o : this->output) {
		if (o.getIdReceiver() == id) {
			return true;
		}
		else {
			return false;
		}
	}
}

void Transaction::generateTxID() {
	string idbase = "";
	for (Input im : input) {
		idbase += im.getBlockID() +im.getUTXOId();
	}
	for (Output out : output) {
		idbase += to_string(out.getAmount()) + out.getIdReceiver();
	}
	this->id = generateIDString(idbase);
}

nlohmann::json Transaction::tranformToJson() {
	nlohmann::json tx;
	tx["TxID"] = this->id;
	for (int i = 0; i < input.size(); i++) {
		tx["input"][i] = input[i].transformToJson();
	}
	for (int i = 0; i < output.size(); i++) {
		tx["output"][i] = output[i].transformToJson();
	}
	return tx;
}
