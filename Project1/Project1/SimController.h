#pragma once
#include "Block.h"
#include "Allegro.h"
class Controller {
public:
	Controller() {}
	bool Tx(Block& orig, Block& dest, unsigned long int monto);
	//void dispatcher(al_event ev, Node* nodo);
	virtual ~Controller() {};
};