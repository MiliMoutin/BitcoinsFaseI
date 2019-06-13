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


Full::Full(string id) {
	this->id = id;
}

void Full::attach(Node* n) {
	this->neighbours.push_back(n);
	notifyAllObservers();
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

void Full::injectBlock(Block b) {
	MerkleRoot* mr = createTree(b);
	b.setRoot(mr);
	this->blockchain.push_back(b);
	//si tengo filtro voy y busco si hay alguno trasacción de ellos
	if (!this->filters.empty()) {
		for (string id : filters) {
			SearchForFilterTransactions(b, id);
		}
	}

	notifyAllObservers();			//esto iria aca???????????
}

MerkleRoot* Full::createTree(Block b) {
	//inicializo el indice que me va a ayudar a iterar sobre las transacciones
	int index = 0;
	int cantCicle;
	//Calculo cantidad de niveles que tiene el arbol

	//creo el vector de transacciones que voy a usar
	vector<Transaction> treeVector = createVectorForTree(b.getTxs(), &cantCicle);
	//empiezo a armar el arbol
	MerkleNode* left = createTreeRec(cantCicle - 1, treeVector, &index);
	MerkleNode* right = createTreeRec(cantCicle - 1, treeVector, &index);

	//genero el id del MerkleRoot
	string id_to_make = to_string(left->getBlockId()) + to_string(right->getBlockId());
	MerkleRoot* m = new MerkleRoot(generateIDString(id_to_make));

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

		unsigned long id1 = rta1->getBlockId();
		unsigned long id2 = rta2->getBlockId();
		unsigned long id_generated = generateIDString(to_string(id1) + to_string(id2));

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
					spv->notify(to_send, this->blockchain.back().getHeader());
				}
			}
		}
	}
	return true;
}

EDAMerkleBlock Full::getTreeInfo(string id) {

	list<Path> paths;
	list<Transaction> transactions;
	list<unsigned long>ids;

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

Path Full::getPath(MerkleRoot* mr, unsigned long id) {

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

bool Full::searchPathRec(MerkleNode* mn, Path& path, unsigned long id, bool& found) {
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
		Transaction(generateIDString(to_string(initial.back().getId()) + to_string(txs)));
		initial.push_back(initial.back());
		txs++;
	}
	return initial;
}

void Full::makeTx(string publicId, double EDACoins) {
	Node::makeTx(publicID, EDACoins);
		if (canDoTx(EDACoins)) {
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

void Full::receiveTx(nlohmann::json tx, Node* who) {
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

			//Aca deberia verificar la firma
			receivedTx.push_back(t);

			/*Ahora se lo mando a mis vecinos menos al que me lo mando*/
			for (Node* n : neighbours) {
				if (n->getType() == "Miner" || n->getType() == "Full" && n != who) {
					Full* f = (Full*)n;
					f->receiveTx(tx, this);
				}
			}
		}
}


Transaction Full::transformJStoTx(nlohmann::json tx) {
	vector<Input> inp;
	vector<Output> outp;
	for (int i = 0; i < tx["input"].size(); i++) {
		string bi = tx["input"][i]["BlockID"];
		string signa = tx["input"][i]["signature"];
		string utxoid = tx["input"][i]["UTXOID"];
		string publick = tx["output"][i]["PublicKey"];
		string edac = tx["output"][i]["EDACoins"];

		Input in(strtoul(bi.c_str(), NULL, 0), strtoul(utxoid.c_str(), NULL, 0), signa);
		Output out(publick, strtoul(edac.c_str(), NULL, 0));
		inp.push_back(in);
		outp.push_back(out);
	}
	return Transaction(inp, outp);

}

bool Full::checkUTXOinBlockchain(unsigned long id) {
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
			f->receiveTx(tx, this);
		}

	}
}
