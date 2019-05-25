#include "Full.h"

Full::Full(string id) {
	this->id = id;
}

void Full::attach(SPV n) {
	if (n.getType() == "SPV") {
		this->neighbours.push_back(n);
	}
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
			SearchForFilterTransaction(b, id);
		}
	}

}

bool Full::SearchForFilterTransaction(Block b, string id) {
	if (b.isIdPresent(id)){
		HeaderBlock h = b.getHeader();
		list<vector<unsigned long>> paths = getMerklePaths(b, id);
		MerkleStructure* mr = getMerkleBlock(b, id);
		//armo el EDAMerkleBlock
		for (SPV n : this->neighbours) {
			if (n.getId() == id) {
				//notifico
				return true;
			}
		}
	}
}


MerkleStructure* Full::getMerkleBlock(Block b, string id) {
	if (b.getRoot()->getLeft() != nullptr && b.getRoot()->getLeft()->isIdPresent(id)
		&& b.getRoot()->getRight() != nullptr && b.getRoot()->getRight()->isIdPresent(id)) {
		//return b.getRoot();
	}
	else if (b.getRoot()->getLeft()->isIdPresent(id)) {
		return getMerkleBlockRec(b.getRoot()->getLeft(), id);
	}
	else if (b.getRoot()->getRight()->isIdPresent(id)) {
		return getMerkleBlockRec(b.getRoot()->getRight(), id);
	}

}

//nunca va a llegar a nullptr
MerkleStructure* Full::getMerkleBlockRec(MerkleBlock* mb, string id){
	MerkleBlock* left = mb->getLeft();
	MerkleBlock* right = mb->getRight();
	bool lb=left->isIdPresent(id);
	bool rb = right->isIdPresent(id);
	if (lb&&rb) {
		return mb;
	}
	else if (lb && !rb) {
		getMerkleBlockRec(left, id);
	}
	else if (!lb&&rb) {
		getMerkleBlockRec(right, id);
	}
}

list<vector<unsigned long>> Full::getMerklePaths(Block b, string id) {
	list<vector<unsigned long>> paths;
	if (b.getRoot()->getLeft()->isIdPresent(id)) {
		vector<unsigned long> path;
		getMerklePathsRec(b.getRoot()->getLeft(), id, path, &paths);
	}
	if (b.getRoot()->getRight()->isIdPresent(id)) {
		vector<unsigned long> path;
		getMerklePathsRec(b.getRoot()->getRight(), id, path, &paths);
	}
}

void Full::getMerklePathsRec(MerkleBlock* mb, string id, vector<unsigned long> path, list<vector<unsigned long>>* paths) {
	path.push_back(mb->getBlockId());
	MerkleBlock* left = mb->getLeft();
	MerkleBlock* right = mb->getRight();
	if (left != nullptr && left->isIdPresent(id)) {
		getMerklePathsRec(left, id, path, paths);
	}
	if (right != nullptr && (left == nullptr || !left->isIdPresent(id)) && right->isIdPresent(id)) {
		getMerklePathsRec(right, id, path, paths);
	}
	if (left != nullptr && left->isIdPresent(id) && right != nullptr && right->isIdPresent(id)) {
		vector<unsigned long> aux(path);
		getMerklePathsRec(right, id, aux, paths);
	}
	if (left == nullptr && right == nullptr) {
		paths->push_back(path);
	}
}




