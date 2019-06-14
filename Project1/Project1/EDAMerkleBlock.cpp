#include "EDAMerkleBlock.h"
#include <iostream>

using namespace std;

EDAMerkleBlock::EDAMerkleBlock(list<Transaction> transactions, list<Path> paths, list<string> ids, string blockID) {
	this->transactions = transactions;
	this->paths = paths;
	this->transactionIds = ids;
	this->BlockID = BlockID;
	this->cantTransactions = transactions.size();

}

EDAMerkleBlock::EDAMerkleBlock(nlohmann::json j) {
	for (nlohmann::json jt : j["transaction"]) {
		this->transactions.push_back(Transaction(jt));
		this->transactionIds.push_back(jt["TxID"]);
	}
	for (int i = 0; i < j["Path"].size(); i++) {
		this->paths.push_back(Path(j["Path"][i]));
	}
	string i= j["BlockID"];
	this->BlockID = i;
	
}

Transaction EDAMerkleBlock::getTransaction(string id) {
	for (Transaction t : this->transactions) {
		if (t.getId() == id) {
			return t;
		}
	}
}

nlohmann::json EDAMerkleBlock::TransformToJson() {
	nlohmann::json EDAmb;
	int i = 0;
	for (Transaction t : this->transactions) {
		EDAmb["transaction"][i] = t.tranformToJson();
		EDAmb["transactionId"][i] =t.getId();
		i++;
	}
	EDAmb["BlockID"] = this->BlockID;
	EDAmb["CantTxs"] = to_string(cantTransactions);
	
	std::list<Path>::iterator it;
	
	i = 0;
	for (Path p : paths) {
		EDAmb["Path"][i] = p.TransformToJson();
		i++;
	}
	return EDAmb;
}