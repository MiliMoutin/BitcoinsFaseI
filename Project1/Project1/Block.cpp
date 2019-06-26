#include "Block.h"
#define TXB "transaction"
#define IDB "BlockID"
#define MRB "}"


Block::Block(vector<Transaction> transactions, string id, MerkleRoot* mr) : cantTransactions(transactions.size()) {
	this->transactions = transactions;
	this->id = id;
	this->root = mr;
}

bool Block::isIdPresent(string id) {
	for (Transaction t : transactions)
	{
		if (t.isIDPresent(id)) { return true; }
	}
}

//asumimos que la trasaccion existe
Transaction Block::getTransaction(string id) {
	for (Transaction t : transactions) {
		if (t.getId() == id) {
			return t;
		}
	}
}

Block::Block(nlohmann::json& jsonBlock) {
	string i= jsonBlock[IDB];
	this->id = i;
	for (int j = 0; j < jsonBlock[TXB].size(); j++) {
		nlohmann::json txj = jsonBlock[TXB][j];
		this->transactions.push_back(Transaction(txj));
	}
	this->root = new MerkleRoot(jsonBlock[MRB]);
}

nlohmann::json Block::TransformToJson() {
	nlohmann::json JsonBlock;
	JsonBlock[IDB] = this->id;
	int i = 0;
	for (Transaction t : this->transactions) {
		JsonBlock[TXB][i] = t.tranformToJson();
		i++;
	}
	JsonBlock[MRB] = this->root->TransformToJson();
	return JsonBlock;
}