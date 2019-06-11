#include "Simulation.h"
#include <ctime>    
#include <cstdlib> 


Simulation::Simulation(unsigned int fulln, unsigned int spv, unsigned int miners):correctParameters(true) {
	/*Me fijo si los parametros son correctos*/
	if (fulln + spv + miners> MAXNODES || miners>fulln) {
		this->correctParameters = false;
	}
	else {
		this->fulln = fulln;
		this->spvn = spv;
		this->minersn = miners;
		this->tot = fulln + spvn + minersn;
		//creo la matriz de adyacencia
		adjacenceM = new bool*[tot];
		for (int i = 0; i < tot; i++) {
			adjacenceM[i] = new bool[tot];
			for (int j = 0; j < tot; j++) {
				adjacenceM[i][j] = false;
			}
		}
		createNetwork();
	}
}

void Simulation::createNetwork() {
	string id = "node";
	/*creo los nodos Full, Miner y SPV y los guardo*/
	for (int i = 0; i < fulln; i++) {
		Full* node = new Full(id + to_string(i));
		n.push_back(node);
	}

	for (int i = 0; i < minersn; i++) {
		Miner* node = new Miner(id + to_string(i+fulln));
		n.push_back(node);
	}

	for (int i = 0; i < spvn; i++) {
		SPV* node = new SPV(id + to_string(i + fulln + minersn));
		n.push_back(node);
	}

	//conecto los nodos Full
	connectFulls();

	//me fijo si el grafo es conexo y si necesita algunas conexiones extra
	for (int i = 0; i < fulln + minersn; i++) {
		for (int j = 0; j < fulln + minersn; j++) {
			//si no existe un camino posible entre dos nodos, los conecto
			if (j != i && !connected(n[i], n[j])) {
				n[i]->attach(n[j]);
				n[j]->attach(n[i]);
				adjacenceM[i][j] = adjacenceM[j][i] = true;
			}
		}
	}
	//ahora conecto los nodos SPVs
	connectSPVs();
	
}

void Simulation::connectFulls() {
	
	srand(time(0));

	for (int i = 0; i < fulln + minersn; i++) {
		int found;
		//el ciclo solo se hace si la cantidad de vecinos es menor que dos
		if ((found=n[i]->getNeighbours().size()) < 2) {
			string id = "node";
			bool correct = false;
			int r;
			//busco dos nodos que aun no sean vecinos de nodo n[i]
			while (!correct && found<2) {
				r = rand() % (fulln + minersn);
				correct = (r != i) && !(n[i]->isNeighbour(id + to_string(r)));
				if (correct) {
					n[i]->attach(n[r]);
					n[r]->attach(n[i]);
					//actualizo la matriz de adyacencia;
					adjacenceM[i][r] = adjacenceM[r][i]= true;
					found++;
				}
			}
		}
	}

}

//devuelve si existe una camino posible entre dos nodos
bool Simulation::connected(Node* n1, Node*n2) {
	//hago bfs a ver si llego al otro nodo
	//primero pongo a todos los nodos como "no visitados"
	for (Node* node : n) {
		node->reset();
	}
	//agrego el primero nodo a la cola
	bfsList.push(n1);

	while (!bfsList.empty()) {
		//agarro el primer node de la cola y visito todos sus vecinos y los pongo en la cola
		bfsList.front()->visit();
		for (Node* node : bfsList.front()->getNeighbours()) {
			if (!node->wasVisited()) {
				//si encuentro el nodo que buscaba
				if (n2->getID() == node->getID()) {
					//si encontre el nodo vacio la lista
					while (!bfsList.empty()) {
						bfsList.pop();
					}
					return true;
				}

				node->visit();
				bfsList.push(node);
			}
		}
		bfsList.pop();
	}
	return false;
}

void Simulation::connectSPVs() {
	int j = 0;
	int total = fulln + minersn;
	//por cada nodo SPV elejo al azar nodos Fulls con los cuales conectarlo
	for (int i = total ; i < this->tot; i++) {
		for (int k = 0; k < TOTALCONNECTIONS; k++) {
			n[i]->attach(n[j%total]);
			n[j%total]->attach(n[i]);
			adjacenceM[i][j%total] = adjacenceM[j%total][i] = true;
			j++;
		}
	}
}







