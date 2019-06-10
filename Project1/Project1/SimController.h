#pragma once
#include "Block.h"
#include "Allegro.h"
class Controller {
public:
	Controller(Allegro& orig) { alle = orig; return; };
	bool Tx(Block& orig, Block& dest, unsigned long int monto);
	void dispatcher(al_event ev, Node* nodo);
	virtual ~Controller() {};
private:
	Allegro alle;
};