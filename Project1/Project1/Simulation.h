#pragma once
#include "Subject.h"
#include "Node.h"
#include "Cajita.h"


class Simulation :public Subject
{
public:
	Node* get_nodes() { return nodos; }
	Cajita* get_cajita() { return cajita; }
private:
	Node* nodos;
	Cajita* cajita;


};