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
	Full::makeTx(publicId, EDACoins);
	if (Node::canDoTx(EDACoins)) {
		Node::signTx(Node::to_send);
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

void Miner::startMine() {
	this->mined = 0;
}

void Miner::adjustMine() {
	//Minó x veces-> y 0s
	//1 vez->z=0s
	if (mined == 0 && challenge <= 0) {
		challenge--;
	}
	else if (mined != 0) {
		int aux = (int)ceil(challenge / mined);
		challenge = aux;
	}
}

bool Miner::mine() {
	SHA256 hash;
	string toHash;

	unsigned int nonce = newNonce();




}

string Miner::strToHash() {
	

}

string& Miner::MakeStr(MerkleNode* mn, string& str) {
	MerkleNode* l = mn->getLeft();
	MerkleNode* r = mn->getRight();
	string strl = "";
	string strr = "";
	if (l != nullptr) {
		strl=MakeStr(l, str);
	}
	if (r != nullptr) {
		strr=MakeStr(r, str);
	}
	string rta = mn->getBlockId() + strr + strl;
	return rta;
}