#pragma once

class Transaction {
public:
	Transaction(unsigned long idBlock, unsigned long idUTXO, unsigned long publicID, unsigned long amount);

private:
	unsigned long id;
};