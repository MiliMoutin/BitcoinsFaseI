#pragma once
#include <iostream>
#include "Input.h"
#include "Output.h"
#include <string>
#include "GenerateID.h"

using namespace std;

class Transaction {
public:
	Transaction();
	Transaction(Input input, Output output);
	void setId(unsigned long id) { this->id = id; }
	string idReceiver() { return output.getIdReceiver(); }
	unsigned long amountOutput() { return output.getAmount(); }
	unsigned long getUTXOId() { return this->input.getUTXOId(); }
	unsigned long getId(){ return this->id; }

private:
	Output output;
	Input input;
	unsigned long id;

};