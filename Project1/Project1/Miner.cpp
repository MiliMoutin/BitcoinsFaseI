#include "Miners.h"

bool Miner::isNeighbour(string id) {
	if (this->neighbours.empty()) {
		return false;
	}
	for (Node *n : this->neighbours) {
		if (n->getID() == id) {
			return true;
		}
		return false;
	}
}

void Miner::attach(Node* n) {
	this->neighbours.push_back(n);
}