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

void Full::attach(SPV* n) {
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
		//inicializo iterador
		index = 0;
		//Calculo cantidad de niveles que tiene el arbol
		int cantCicle = (int)ceil(sqrt(b.getCantTxs()));

		//empiezo a armar el arbol
		MerkleNode* left = createTreeRec(cantCicle - 1, b.getTxs());
		MerkleNode* right = createTreeRec(cantCicle - 1, b.getTxs());
		sleep_for(seconds(3));
		string id_to_make = to_string(left->getBlockId()) + to_string(right->getBlockId());
		MerkleRoot* m = new MerkleRoot(generateIDString(id_to_make));
		m->setFirstChildren(left, right);
		return m;
}

MerkleNode* Full::createTreeRec(int cantCicle, vector<Transaction> txsvector) {
		//si la cantidad de ciclo es cero, creo las hojas
		if (cantCicle == 0) {
			Transaction t=txsvector[index++];
			MerkleNode* mn = new MerkleNode();
			mn->setId(t.getId());
			return mn;
		}
		else {
			//primera el left, segundo el right
			MerkleNode* rta1 = createTreeRec(cantCicle -1, txsvector);
			MerkleNode* rta2 = createTreeRec(cantCicle -1, txsvector);
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
		for (SPV* n : this->neighbours) {
			if (n->getId() == id) {
				n->notify(to_send);
			}
		}
	}
	return true;
}

EDAMerkleBlock Full::getTreeInfo(string id) {
	cout << "tamos 2.0?" << endl;
	sleep_for(seconds(3));
	list<Path> paths;
	list<Transaction> transactions;
	list<unsigned long>ids;

	Block last_block = this->blockchain.back();

	for (Transaction t : last_block.getTxs()) {
		if (t.idReceiver() == id) {
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
			path->addID(right->getBlockId());
		}
		else if (searchPathRec(right, *path, id)) {
			path->addID(left->getBlockId());
		}
		return *path;
}


bool Full::searchPathRec(MerkleNode* mn, Path& path, unsigned long id) {
		if (mn->isLastBlock() && id == mn->getBlockId()) {
		return true;
		}
		if (mn->isLastBlock() && id != mn->getBlockId()) {
		return false;
		}
		else {
			MerkleNode* left = mn->getLeft() ;
			MerkleNode* right =mn->getRight();
			bool rtaleft = searchPathRec(left, path, id);
			bool rtaright = searchPathRec(right, path, id);
			if (rtaleft == true) {
				path.addID(right->getBlockId());
			}
			if (rtaright == true) {
				path.addID(left->getBlockId());
			}
			return rtaleft || rtaright;
		}

}





