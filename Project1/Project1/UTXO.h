#pragma once

class UTXO {
public:	
	UTXO(unsigned long amount, unsigned long id) { this->amount = amount;  this->id = id; }
	unsigned long amount() { return this->amount; }
	unsigned long getUTXOId() { return this->id; }
private:
	unsigned long amount;
	unsigned long id;
};