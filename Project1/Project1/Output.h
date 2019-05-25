#pragma once

class Output {
	Output(unsigned long idReceiver, unsigned long amount) { this->idReceiver = idReceiver; this->amount = amount; }
private:
	unsigned long idReceiver;
	unsigned long amount;
};
