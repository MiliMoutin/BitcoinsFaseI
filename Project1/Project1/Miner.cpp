#include "Miners.h"

void Miner::receiveTx(nlohmann::json tx, Node* n) {
	Full::receiveTx(tx, n);
	this->toMine.push_back(Transaction(tx));
}

void Miner::makeTx(string publicId, double EDACoins) {
	Full::makeTx(publicID, EDACoins);
	if (Node::canDoTx(EDACoins)) {
		Full::communicateTx(this->to_send.tranformToJson());
		this->toMine.push_back(this->to_send);
	}
}