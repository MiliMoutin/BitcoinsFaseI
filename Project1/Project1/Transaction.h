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
	Transaction(unsigned long id) { this->id = id; }
	Transaction(vector<Input> input, vector<Output> output);
	void setId(unsigned long id) { this->id = id; }
	unsigned long getId() { return this->id; }
	bool isIDPresent(string id);
	vector<Output> getOutputs() { return output; }
	vector<Input> getInput() { return input; }
	nlohmann::json tranformToJson();

private:
	vector<Output> output;
	vector<Input> input;
	unsigned long id;
	void generateTxID();

};