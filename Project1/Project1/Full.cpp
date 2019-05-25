#include "Full.h"

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
	this->blockchain.push_back(b);
	this->merkleroots.push_back(b.getRoot());

	//si tengo filtro voy y busco si hay alguno trasacción de ellos
	if (!this->filters.empty()) {
		for (string id : filters) {
			SearchForFilterTransactions(b, id);
		}
	}

}

bool Full::SearchForFilterTransactions(Block b, string id) {
	if (b.isIdPresent(id)){
		HeaderBlock h = b.getHeader();
		EDAMerkleBlock to_send = getTreeInfo(b, id);
		for (SPV* n : this->neighbours) {
			if (n->getId() == id) {
				n->notify(h, to_send);
				return true;
			}
		}
	}
}

EDAMerkleBlock Full::getTreeInfo(Block b, string id) {
	list<vector<unsigned long>> paths;
	list<Transaction> transactions;

		vector<unsigned long> pathl;
		getTreeInfoRec(b.getRoot()->getLeft(), id, pathl, &paths, &transactions);
		vector<unsigned long> pathr;
		getTreeInfoRec(b.getRoot()->getRight(), id, pathr, &paths, &transactions);

	return EDAMerkleBlock(transactions, paths);
}

void Full::getTreeInfoRec(MerkleBlock* mb, string id, vector<unsigned long> path, list<vector<unsigned long>>* paths, list<Transaction>* transactions) {
	path.push_back(mb->getBlockId());
	MerkleBlock* l = mb->getLeft();
	MerkleBlock* r = mb->getRight();
	if (mb->isLastBlock() && mb->getTransaction().idReceiver()==id) {
		//pusheo path a la lista de paths
		paths->push_back(path);
		transactions->push_back(mb->getTransaction());
	}
	else {
		getTreeInfoRec(l, id, path, paths, transactions);
		getTreeInfoRec(r, id, path, paths, transactions);
	}
	
}




