#pragma once
#include "Input.h"
#include "Output.h"

class Transaction {
public:
	Transaction();
	string idReceiver() { return output.getIdReceiver(); }
	unsigned long amountOutput() { return output.getAmount(); }

private:
	string id;
	Output output;
	Input input;
};