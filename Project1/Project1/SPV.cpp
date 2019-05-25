#include "SPV.h"

void SPV::attach(Node* n) {
	this->neighbours.push_back(n);
}

void SPV::notify(HeaderBlock h, EDAMerkleBlock md) {
	this->headers.push_back(h);
	//el SPV tiene que validar que el path es correcto

}

