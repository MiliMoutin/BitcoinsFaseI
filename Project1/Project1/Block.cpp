#include "Block.h"

Block::Block(vector<Transaction> transactions, unsigned long id, MerkleRoot* mr) : cantTransactions(transactions.size()) {
	this->transactions = transactions;
	this->id = id;
	this->root = mr;
}

bool Block::isIdPresent(string id) {
	for (Transaction t : transactions)
	{
		if (t.idReceiver() == id) { return true; }
	}
}

//asumimos que la trasaccion existe
Transaction Block::getTransaction(unsigned long id) {
	for (Transaction t : transactions) {
		if (t.getId() == id) {
			return t;
		}
	}
}