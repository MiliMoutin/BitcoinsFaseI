#pragma once


class UTXO {
public:	
	UTXO(double amount) { this->amount = amount; }
	UTXO(double amount, string id) { this->amount = amount;  this->id = id; }
	double getAmount() { return this->amount; }
	string getUTXOId() { return this->id; }
private:
	double amount;
	string id;
};