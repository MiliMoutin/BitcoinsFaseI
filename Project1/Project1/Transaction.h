#pragma once
#include "Input.h"
#include "Output.h"
class Transaction {
public:
	Transaction();
	void pushImput(Input i) {
		this->inputs.push_back(i);
	}
	void pushOutput(Output o) {
		this->outputs.push_back(o);
	}

private:
	string id;
	vector<Output> outputs;
	vector<Input> inputs;
};