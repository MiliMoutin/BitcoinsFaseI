#include "Transaction.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

Transaction::Transaction(vector<Input> input, vector<Output> output){
	this->input = input;
	this->output = output;
}

string Transaction::getId() {
	string rta = "";
	for (Input& i : this->input) {
		for (byte b : i.getSignature()) {
			rta += to_string(b);
		}
	}
	return rta;
	this->id = rta;
}

string Transaction::toSign() {
	string rta = " ";
	for (Input i: input) {
		rta += i.toSign();
	}
	for (Output o : output) {
		rta += o.toSign();
	}
	return rta;
}

Transaction::Transaction(nlohmann::json& j) {
	int i = 0;
	string d = j["TxID"];
	this->id = d;
	for(int k=0; k<j["input"].size(); k++) {
		Input i(j["input"][i]);
		this->input.push_back(i);
	}
	i = 0;
	for (int k = 0; k < j["input"].size(); k++) {
		Output o(j["output"][k]);
		this->output.push_back(o);
	}
}

bool Transaction::operator==(Transaction t) {
	return t.getId() == id;
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
