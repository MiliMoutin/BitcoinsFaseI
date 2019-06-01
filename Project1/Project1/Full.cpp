#include "Full.h"
#include <string>
#include "MerkleNode.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


Full::Full(string id) {
	this->id = id;
}

void Full::attach(Node* n) {
		this->neighbours.push_back(n);
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
		sleep_for(seconds(20));
}

MerkleNode* Full::createTreeRec(int cantCicle, vector<Transaction> txsvector, int* index) {
		//si la cantidad de ciclos es cero, creo las hojas
		if (cantCicle == 0) {
			Transaction t=txsvector[(*index)++];
			MerkleNode* mn = new MerkleNode();
			mn->setId(t.getId());

			return mn;
		}
		else {
			//primera el left, segundo el right
			MerkleNode* rta1 = createTreeRec(cantCicle -1, txsvector, index);
			MerkleNode* rta2 = createTreeRec(cantCicle -1, txsvector, index);

			unsigned long id1 = rta1->getBlockId();
			unsigned long id2 = rta2->getBlockId();
			unsigned long id_generated=generateIDString(to_string(id1) + to_string(id2));

			MerkleNode* rtafinal = new MerkleNode();
			rtafinal->setId(id_generated);

			rtafinal->setLeft(rta1);
			rtafinal->setRight(rta2);

			return rtafinal;
		}
}



bool Full::SearchForFilterTransactions(Block b, string id) {
	if (b.isIdPresent(id)){
		EDAMerkleBlock to_send = getTreeInfo(id);
		for (Node* n : this->neighbours) {
			if (n->getType() == "SPV") {
				SPV* spv=(SPV*)n;
				if (spv->getID() == id) {
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
	MerkleNode* right = mr->getRight();
	if (searchPathRec(left, *path, id)) {
		path->addID(right->getBlockId(), RIGHT);
	}
	else if (searchPathRec(right, *path, id)) {
		path->addID(left->getBlockId(), LEFT);
	}
	return *path;

}

bool Full::searchPathRec(MerkleNode* mn, Path& path, unsigned long id) {
		if (mn->isLastBlock() && id == mn->getBlockId()) {
		return true;
		}
		else if (mn->isLastBlock() && id != mn->getBlockId()) {
		return false;
		}
		else {
			MerkleNode* left = mn->getLeft() ;
			MerkleNode* right =mn->getRight();

			bool rtaleft = searchPathRec(left, path, id);
			bool rtaright = searchPathRec(right, path, id);

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

//se fija si un numero es cuadrado perfecto
bool Full::isPot2(int cant, int* exponent) {
	for (int i = 0; pow(2,i)<= cant; i++) {
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
	destroyTree(nd->getLeft());
	destroyTree(nd->getRight());
	delete nd;
}

																																																					



