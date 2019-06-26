#pragma once
#include "Subject.h"
#include "Node.h"
#include "Full.h"
#include "Cajita.h"
#include "nlohmann/json.hpp"
#include "Miners.h"
#include <map>
#include <vector>
#include <time.h>
#include <iostream>
#include <queue>

#define MAXNODES 20
#define TOTALCONNECTIONS 2

using namespace std;
using namespace std::chrono;


class Simulation :public Subject
{
public:
	/*Siempre despues de inicializar hay que preguntar si la creacion fue exitosa*/
	Simulation(unsigned int fulln, unsigned int spv, unsigned int miners);
	bool creationSuccessful() { return this->correctParameters; }
	vector<Node*> get_nodes() { return n; }
	vector<Cajita*> get_cajita(){ return cajita; }
	int get_total() { return tot; }
	bool** get_adyM() { return adjacenceM; }
	void keepMining();
	void createTx(string idEmission, string idReceiver, double amount);
	void printMatrix();
	void destroySim();

private:
	vector<Cajita*> cajita;
	bool correctParameters;
	Miner* Satochi;

	clock_t start;
	bool started;
	int fulln;
	int spvn;
	int minersn;
	int tot;
	bool txsPresent;
	bool ** adjacenceM;
	vector<Node*> n;

	void createNetwork();
	void connectFulls();
	void connectSPVs();


	bool allVisited();
	void connectGraph(Node* n, int index);
	queue<Node*> bfsList;
	void startCoinCirculation();
	vector<Miner*> miners;

	Miner* lastMined;
};