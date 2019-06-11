#include "Miners.h"

bool Miner::isNeighbour(string id) {
	if (this->neighbours.empty()) {
		return false;
	}
	for (Node *n : this->neighbours) {
		if (n->getID() == id) {
			return true;
		}
		return false;
	}
}

void Miner::attach(Node* n) {
	this->neighbours.push_back(n);
}

void Miner::receiveTx(nlohmann::json tx) {
	bool received = false;
	Transaction t = transformJStoTx(tx);
	//me fijo si la transaccion ya fue previamente recibida
	if (!receivedTx.empty()) {
		for (Transaction transac : receivedTx) {
			if (t.getId() == transac.getId()) {
				received = true;
			}
		}
	}
	if (!received) {
		/*chequeo que la transacción que me llego tenga UTXO que no fueron utilizados antes*/
		for (Input i : t.getInput()) {
			if (!checkUTXOinBlockchain(i.getUTXOId())) {
				/*Que hacemos si hay un double spend*/
			}
		}
		/*Me fijo si ya recibí la transacción*/
		receivedTx.push_back(t);
		toMine.push_back(t);
	}

}