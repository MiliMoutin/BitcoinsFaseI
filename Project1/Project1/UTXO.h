#pragma once

class UTXO {
public:	
	UTXO(string publicId, unsigned long amount);
	string getPublicId() { return this->publicId; }
	unsigned long amount() { return this->amount; }
private:
	string publicId;
	unsigned long amount;
};