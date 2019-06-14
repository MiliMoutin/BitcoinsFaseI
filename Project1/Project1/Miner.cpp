#include "Miners.h"

void Miner::receiveTx(nlohmann::json tx, Node* n) {
	Full::receiveTx(tx, n);
	bool received = false;
	Transaction txx(tx);
	for (Transaction t : Full::receivedTx) {
		if (t == txx) {
			received = true;
		}
	}
	if (!received) {
		this->toMine.push_back(Transaction(tx));
	}
}

void Miner::makeTx(string publicId, double EDACoins) {
	Full::makeTx(publicID, EDACoins);
	if (Node::canDoTx(EDACoins)) {
		Full::communicateTx(this->to_send.tranformToJson());
		this->toMine.push_back(this->to_send);
	}
}

void Miner::sendBlock() {
	Block b(toMine, "Bloque1");
	b.setRoot(Full::createTree(b));
	nlohmann::json jsonblock = b.TransformToJson();
	for (Node* n : neighbours) {
		Full* f = (Full*)n;
		f->injectBlock(jsonblock);
	}
}