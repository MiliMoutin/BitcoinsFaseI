#pragma once
#include "Input.h"
#include "Output.h"

class Transaction {
public:
	Transaction();
	string idReceiver() { return output.getIdReceiver(); }

private:
	string id;
	Output output;
	Input input;
};