#pragma once
#include <iostream>
#include "Input.h"
#include <nlohmann/json.hpp>
#include "Output.h"
#include <string>
#include <vector>
#include "GenerateID.h"

using namespace std;

class Transaction {
public:
	Transaction(){}
	Transaction(nlohmann::json& j);
	Transaction(string id) { this->id = id; }
	void setInput(vector<Input> i) { this->input = i; }
	Transaction(vector<Input> input, vector<Output> output);
	void setId(string id) { this->id = id; }
	string getId(); 
	bool isIDPresent(string id);
	vector<Output> getOutputs() { return output; }
	vector<Input> getInput() { return input; }
	nlohmann::json tranformToJson();
	bool operator==(Transaction t);
	string toSign();

private:
	vector<Output> output;
	vector<Input> input;
	string id;
	void generateTxID();

};