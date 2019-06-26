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


void Miner::startMine() {
	this->mined = 0;
}

void Miner::adjustMine() {
	//Minó x veces-> y 0s
	//1 vez->z=0s
	if (mined == 0 && challenge < 0) {
		challenge--;
	}
	else if (mined != 0) {
		int aux = (int)ceil(challenge / mined);
		challenge = aux;
	}
}

bool Miner::mine() {
	SHA256 hash;
	unsigned int nonce;
	string toHash = strToHash(nonce);
	string hashed=Node::crypp.hashSHA256(toHash);

	vector<byte> hashedByt;
	//transformo hash en un arreglo de bytes
	for (int i = 0; i < hashed.size(); i++) {
		byte b;
		std::stringstream aux;
		aux << hashed[i] + hashed[i + 1];
		aux >> std::hex >> b;
		hashedByt.push_back(b);
	}
	//me fijo si se cumple el challenge, es decir lo primeros bits son 0.
	unsigned int chall = challenge;
	for(int hash=0; hash<hashedByt.size() && chall!=0; hash++){
		byte x = hashedByt[hash];
		for (int bit= 0; bit < 7 && chall!=0; bit++) {
			//me fijo si el primero bit está en cero
			x = hashedByt[hash] & CHALLENGEMASK;
			if (x == CHALLENGEMASK) {
				return false;
			}
			x=x << 1;
		}
	}

}

unsigned int Miner::newNonce() {
	unsigned int nonce = 0x00000000;
	unsigned int increment = INCREMENT;
	int aux = 32;

	//pongo un nonce random
	while (aux != 0) {
		increment = increment << 1;
		if (rand() % 2 == 0) {
			nonce= nonce | increment;
		}
		aux--;
	}
	return aux;
}

string Miner::strToHash(unsigned int& non) {
	
	string strn = "";

	
	//escribo los bits correspondientes al nonce
	srand(time(0));
	unsigned int nonce = newNonce();
	non = nonce;
	strn += to_string(nonce);
	
	//escribo los bits correspondientes al Header
	MerkleRoot* mr = Full::createTree(Block(this->toMine));
	MakeStr(mr->getLeft(), strn);
	MakeStr(mr->getRight(), strn);

	strn += blockchain.back().getId();

	return strn;
}

string Miner::Challenge() {

	unsigned long chal = 0x00000000;
	int aux = challenge;
	unsigned long increment = INCREMENT;
	while (aux != 0) {
		increment = increment << 1;
		chal = chal | increment;
		aux--;
	}
	return to_string(chal);
}


string& Miner::MakeStr(MerkleNode* mn, string& str) {
	string rta = "";
	if (mn != nullptr) {
		MerkleNode* l = mn->getLeft();
		MerkleNode* r = mn->getRight();
		string strl = "";
		string strr = "";
		if (l != nullptr) {
			strl = MakeStr(l, str);
		}
		if (r != nullptr) {
			strr = MakeStr(r, str);
		}
		rta += mn->getBlockId() + strr + strl;
	}
	return rta;
}