#pragma once

class Output {
public:
	Output(unsigned long idReceiver, unsigned long amount) { this->idReceiver = idReceiver; this->amount = amount; }
	string getIdReceiver() { return idReceiver; }
private:
	string idReceiver;
	unsigned long amount;
};
