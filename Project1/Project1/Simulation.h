#pragma once
#include "Subject.h"
#include "Node.h"
#include "Full.h"
#include "Node.h"
#include "Cajita.h"
#include "Miners.h"
#include <map>
#include <vector>
#include <iostream>
#include <queue>

#define MAXNODES 20
#define TOTALCONNECTIONS 2

using namespace std;


class Simulation :public Subject
{
public:
	/*Siempre despues de inicializar hay que preguntar si la creacion fue exitosa*/
	Simulation(unsigned int fulln, unsigned int spv, unsigned int miners);
	bool creationSuccessful() { return this->correctParameters; }
	Node* get_nodes() { return nodos; }
	Cajita get_cajita(){ return cajita; }
	int get_total() { return tot; }
	bool** get_adyM() { return adjacenceM; }
	void createTx(string idEmission, string idReceiver, double amount);

private:
	Node* nodos;
	Cajita cajita;
	bool correctParameters;

	int fulln;
	int spvn;
	int minersn;
	int tot;
	bool ** adjacenceM;
	vector<Node*> n;

	void createNetwork();
	void connectFulls();
	void connectSPVs();
	bool connected(Node* n1, Node* n2);

	queue<Node*> bfsList;

};