#include "Block.h"

Block::Block(vector<Transaction> transactions):root() {
	this->transactions = transactions;
}

bool Block::isIdPresent(string id) {
	for (Transaction t : transactions)
	{
		if (t.idReceiver() == id) { return true; }
	}
}

Transaction Block::getTransaction(unsigned long id) {
	for (Transaction t : transactions) {
		if (t.getId == id) {
			return t;
		}
	}
}