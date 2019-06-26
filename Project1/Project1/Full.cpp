#include "Full.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include "MerkleNode.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;
using namespace std;


Full::Full(string id):receivedFirst(false) {
	this->id = id;
	Node::createPPKey();
}

void Full::attach(Node* n) {
	this->neighbours.push_back(n);
	notifyAllObservers();
	if (n->getType() == "SPV") {
		setFilter(n->getID());
	}
	return;
}

bool Full::isNeighbour(string id) {
	if (this->neighbours.empty()) {
		return false;
	}
	for (Node *n : this->neighbours) {
		if (n->getPublicID() == id) {
			return true;
		}
		return false;
	}
}

void Full::setFilter(string id) {
	this->filters.push_back(id);
}

void Full::injectBlock(nlohmann::json& jsonBlock, nlohmann::json& nonce) {
	Block b(jsonBlock);
	MerkleRoot* mr = createTree(b);
	b.setRoot(mr);
	string nonceStr = nonce["nonce"];
	unsigned int nonce_ = strtoul(nonceStr.c_str(), NULL, 10);
	if (checkBlockValidity(b, nonce_)) {
		this->blockchain.push_back(b);
		//si tengo filtro voy y busco si hay alguno trasacción de ellos
		if (!this->filters.empty()) {
			for (string id : filters) {
				SearchForFilterTransactions(b, id);
			}
		}
		this->TxOfInterest(b);
	}

	notifyAllObservers();			
}

void Full::TxOfInterest(Block b) {
	vector<Transaction> txsInterest;
	for (Transaction t : b.getTxs()) {
		for (Output o : t.getOutputs()) {
			if (o.getIdReceiver() == this->publicId) {
				double amo = o.getAmount();
				this->UTXOs.push_back(UTXO(amo, to_string(Node::getUTXOId(o.getAmount, o.getIdReceiver(), t.getId()))));
			}
		}
	}
}


bool Full::checkBlockValidity(Block B, unsigned int& nounce) {
	string strn = "";

	//escribo los bits correspondientes al nonce
	strn += to_string(nounce);

	//escribo los bits correspondientes al Header
	vector<Transaction> txs;
	for (Transaction t : B.getTxs()) {
		txs.push_back(t);
	};

	MerkleRoot* mr = Full::createTree(Block(txs));
	MakeStr(mr->getLeft(), strn);
	MakeStr(mr->getRight(), strn);
	if (!blockchain.empty()) {
		strn += blockchain.back().getId();
	}

	return (B.getId()== Node::crypp.hashSHA256(strn));
}

string Full::MakeStr(MerkleNode* mn, string& str) {
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

MerkleRoot* Full::createTree(Block b) {
	//inicializo el indice que me va a ayudar a iterar sobre las transacciones
	int index = 0;
	int cantCicle;
	if (b.getCantTxs() == 1) {
		MerkleRoot* mn = new MerkleRoot();
		mn->setId(b.getId());
		return mn;
	}
	//Calculo cantidad de niveles que tiene el arbol
	//creo el vector de transacciones que voy a usar
	vector<Transaction> treeVector = createVectorForTree(b.getTxs(), &cantCicle);
	//empiezo a armar el arbol
	MerkleNode* left = createTreeRec(cantCicle - 1, treeVector, &index);
	MerkleNode* right = createTreeRec(cantCicle - 1, treeVector, &index);

	//genero el id del MerkleRoot
	string id_to_make = left->getBlockId() + right->getBlockId();
	MerkleRoot* m = new MerkleRoot(to_string(generateIDString(id_to_make)));

	m->setFirstChildren(left, right);

	return m;
	
}

MerkleNode* Full::createTreeRec(int cantCicle, vector<Transaction> txsvector, int* index) {
	//si la cantidad de ciclos es cero, creo las hojas
	if (cantCicle == 0) {
		Transaction t = txsvector[(*index)++];
		MerkleNode* mn = new MerkleNode();
		mn->setId(t.getId());

		return mn;
	}
	else {
		//primera el left, segundo el right
		MerkleNode* rta1 = createTreeRec(cantCicle - 1, txsvector, index);
		MerkleNode* rta2 = createTreeRec(cantCicle - 1, txsvector, index);

		string id1 = rta1->getBlockId();
		string id2 = rta2->getBlockId();
		//ACA IRÍA EL ID HASHEADO
		string id_generated = "ID";

		MerkleNode* rtafinal = new MerkleNode();
		rtafinal->setId(id_generated);

		rtafinal->setLeft(rta1);
		rtafinal->setRight(rta2);

		return rtafinal;
	}
}



bool Full::SearchForFilterTransactions(Block b, string id) {
	if (b.isIdPresent(id)) {
		EDAMerkleBlock to_send = getTreeInfo(id);
		for (Node* n : this->neighbours) {
			if (n->getType() == "SPV") {
				SPV* spv = (SPV*)n;
				if (spv->getPublicID() == id) {
					spv->notify(to_send.TransformToJson(), b.getHeader().TransformToJson());
				}
			}
		}
	}
	return true;
}

EDAMerkleBlock Full::getTreeInfo(string id) {

	list<Path> paths;
	list<Transaction> transactions;
	list<string>ids;

	Block last_block = this->blockchain.back();

	for (Transaction t : last_block.getTxs()) {
		if (t.isIDPresent(id)) {
			MerkleRoot * mr = last_block.getRoot();
			paths.push_back(getPath(mr, t.getId()));
			transactions.push_back(t);
			ids.push_back(t.getId());
		}
	}
	return EDAMerkleBlock(transactions, paths, ids, last_block.getId());
}

Path Full::getPath(MerkleRoot* mr, string id) {

	Path* path = new Path();
	MerkleNode* left = mr->getLeft();
	bool found = false;
	MerkleNode* right = mr->getRight();
	if (searchPathRec(left, *path, id, found)) {
		path->addID(right->getBlockId(), RIGHT);
	}
	else if (searchPathRec(right, *path, id, found)) {
		path->addID(left->getBlockId(), LEFT);
	}
	return *path;
}

bool Full::searchPathRec(MerkleNode* mn, Path& path, string id, bool& found) {
	if (mn->isLastBlock() && id == mn->getBlockId() && !found) {
		found = true;
		return true;
	}
	else if (mn->isLastBlock() && (id != mn->getBlockId() || found)) {
		return false;
	}
	else {
		MerkleNode* left = mn->getLeft();
		MerkleNode* right = mn->getRight();

		bool rtaleft = searchPathRec(left, path, id, found);
		bool rtaright = searchPathRec(right, path, id, found);

		if (rtaleft) {
			path.addID(right->getBlockId(), RIGHT);
		}
		if (rtaright) {
			path.addID(left->getBlockId(), LEFT);
		}
		return rtaleft || rtaright;
	}

}

//crea un vector de transaccion que tenga el tamaño de un cuadrado perfecto
vector<Transaction> Full::createVectorForTree(vector<Transaction> initial, int* height) {
	int txs = initial.size();
	while (!isPot2(txs, height) || txs % 2 != 0) {
		Transaction(to_string(generateIDString(initial.back().getId() + to_string(txs))));
		initial.push_back(initial.back());
		txs++;
	}
	return initial;
}

void Full::makeTx(string publicId, double EDACoins) {
	Node::makeTx(publicId, EDACoins);
		if (canDoTx(EDACoins)) {
			Node::signTx(Node::to_send);
			communicateTx(to_send.tranformToJson());
		}
}


//se fija si un numero es cuadrado perfecto
bool Full::isPot2(int cant, int* exponent) {
	for (int i = 0; pow(2, i) <= cant; i++) {
		if (pow(2, i) == cant) {
			*exponent = i;
			return true;
		}
	}
	return false;
}

void Full::destroyBlockchain() {
	for (MerkleRoot* b : this->merkleroots) {
		destroyTree(b->getLeft());
		destroyTree(b->getRight());
	}
	notifyAllObservers();
}

void Full::destroyTree(MerkleNode* nd) {
	if (nd->isLastBlock()) {
		delete nd;
	}
	else {
		destroyTree(nd->getLeft());
		destroyTree(nd->getRight());
		delete nd;
	}
}

void Full::receiveTx(nlohmann::json tx, Node* who, ECDSA<ECP, SHA256>::PublicKey& pk) {
	Node::received = false;
		Transaction t(tx);
		//me fijo si la transaccion ya fue previamente recibida
		if (receivedTx.size()!=0) {
			for (Transaction transac : receivedTx) {
				if (t.getId() == transac.getId()) {
					Node::received = true;
				}
			}
		}
		if (!Node::received /*&& Node::verifyTx(t,pk)*/) {
			
			/*Me fijo si la firma esta bien*/
			/*chequeo que la transacción que me llego tenga UTXO que no fueron utilizados antes*/
			for (Input i : t.getInput()) {
				if (!checkUTXOinBlockchain(i.getUTXOId())) {
					/*Que hacemos si hay un double spend*/
				}
			}

			//Aca deberia verificar la firma
			receivedTx.push_back(t);

			/*Ahora se lo mando a mis vecinos menos al que me lo mando*/
			for (Node* n : neighbours) {
				if (n->getType() == "Miner" || n->getType() == "Full" && n != who) {
					Full* f = (Full*)n;
					f->receiveTx(tx, this, pk);
				}
			}
		}
		notifyAllObservers();
}

bool Full::checkUTXOinBlockchain(string id) {
	if (!blockchain.empty()) {
		for (Block b : blockchain) {
			for (Transaction t : b.getTxs()) {
				for (Input i : t.getInput()) {
					if (i.getUTXOId() == id) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

void Full::communicateTx(nlohmann::json tx) {
	for (Node* n : neighbours) {
		if (n->getType() == "Miner" || n->getType() == "Full") {
			Full* f = (Full*)n;
			ECDSA<ECP, SHA256>::PublicKey pk;
			pk = this->getPk();
			f->receiveTx(tx, this, pk);
		}

	}
}
