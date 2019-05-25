#pragma once
#include <iostream>
#include "Input.h"
#include "Output.h"
#include <string>

using namespace std;

class Transaction {
public:
	Transaction();
	Transaction(Input input, Output output);
	string idReceiver() { return output.getIdReceiver(); }
	unsigned long amountOutput() { return output.getAmount(); }
	unsigned long getUTXOId() { return this->input.getUTXOId(); }

private:
	Output output;
	Input input;
	string id;

};