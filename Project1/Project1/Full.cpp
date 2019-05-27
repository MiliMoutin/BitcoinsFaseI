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
				n->notify(to_send);
				return true;
			}
		}
	}
}

EDAMerkleBlock Full::getTreeInfo(Block b, string id) {
	list<vector<unsigned long>> paths;
	list<Transaction> transactions;

		vector<unsigned long> pathl;
		getTreeInfoRec(b, b.getRoot()->getLeft(), id, pathl, &paths, &transactions);
		vector<unsigned long> pathr;
		getTreeInfoRec(b, b.getRoot()->getRight(), id, pathr, &paths, &transactions);

	return EDAMerkleBlock(transactions, paths, b.getId());
}

void Full::getTreeInfoRec(Block b, MerkleNode* mb, string id, vector<unsigned long> path, list<vector<unsigned long>>* paths, list<Transaction>* transactions) {
	//pusheo el block ID a mi lista de paths
	path.push_back(mb->getBlockId());
	
	//si mb es una hoja y es una de las transacciones de SPV que estoy buscando, pusheo el path encontrado y la transación
	if (mb->isLastBlock()) {
		Transaction t = b.getTransaction(mb->getBlockId());
		if (t.idReceiver() == id) {
			paths->push_back(path);
			transactions->push_back(t);
		}
	}
	//si mb no es una hoja, sigo buscando
	else {
		MerkleNode* l = mb->getLeft();
		MerkleNode* r = mb->getRight();
		getTreeInfoRec(b, l, id, path, paths, transactions);
		getTreeInfoRec(b, r, id, path, paths, transactions);
	}
	
}




