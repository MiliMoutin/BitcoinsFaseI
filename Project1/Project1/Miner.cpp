#include "Miners.h"
#define MINERTXWIN 300

void Miner::receiveTx(nlohmann::json tx, Node* n, ECDSA<ECP, SHA256>::PublicKey& pk) {
	Full::receiveTx(tx, n, pk);
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

void Miner::adjustMine(double start, double end) {
	//Minó x veces-> y 0s
	//1 vez->z=0s
	if (challenge > 0) {
		challenge--;
	}
	else if (mined != 0) {
		int aux = (int)ceil(challenge*60/end-start);
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
		string strbyt= to_string(hashed[i]) + to_string(hashed[i + 1]);
		aux << strbyt;
		aux >> std::hex >> b;
		hashedByt.push_back(b);
	}
	//me fijo si se cumple el challenge, es decir lo primeros bits son 0.
	unsigned int chall = challenge;
	for(int hash=0; hash<hashedByt.size()&& chall!=0; hash++){
		char x = hashedByt[hash];
		for (int bit= 0; bit < 7&& chall!=0; bit++) {
			//me fijo si el primero bit está en cero
			x = hashedByt[hash] & CHALLENGEMASK;
			if (x == CHALLENGEMASK) {
				return false;
			}
			x=x << 1;
			chall--;
		}
	}
	this->toMine.push_back(this->createWinnerTransaction());
	this->lastMined = Block(this->toMine, hashed);
	this->winnerNonce = nonce;
	return true;
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
	return nonce;
}

string Miner::strToHash(unsigned int& non) {
	
	string strn = "";

	//escribo los bits correspondientes al nonce
	srand(time(0));
	unsigned int nonce = newNonce();
	non = nonce;
	strn += to_string(nonce);
	
	//escribo los bits correspondientes al Header
	vector<Transaction> ToMine;
	for (Transaction t : this->toMine) {
		ToMine.push_back(t);
	}
	ToMine.push_back(this->createWinnerTransaction());
	MerkleRoot* mr = Full::createTree(Block(ToMine));
	MakeStr(mr->getLeft(), strn);
	MakeStr(mr->getRight(), strn);

	if (!blockchain.empty()) {
		strn += blockchain.back().getId();
	}

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


void Miner::hasMined() {
	this->lastMined.setRoot(Full::createTree(this->lastMined));
	for (Node* n : this->neighbours) {
		if (n->getType() == "Full" || n->getType() == "Miner") {
			Full* f = (Full*)n;
			nlohmann::json JsonNonce;
			JsonNonce["Block"] = to_string(this->winnerNonce);
			nlohmann::json block_ = this->lastMined.TransformToJson();
			f->injectBlock(block_, JsonNonce);
		}
	}
}

Transaction Miner::createWinnerTransaction() {
	Input imp("bloquesin", to_string(generateIDString(to_string(this->blockchain.size()))),this->publicId);
	Output out(this->publicId, MINERTXWIN);
	vector<Input> i;
	vector<Output> o;
	string impStr = imp.toSign();
	imp.setSignature(crypp.getSignature(this->privateKey, impStr));
	i.push_back(imp);
	o.push_back(out);
	return Transaction(i, o);
}