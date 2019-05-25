#pragma once

class UTXO {
public:	
	UTXO(unsigned long amount) { this->amount = amount; }
	unsigned long amount() { return this->amount; }
private:
	unsigned long amount;
};