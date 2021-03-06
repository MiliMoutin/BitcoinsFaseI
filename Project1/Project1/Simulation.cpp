#include "Simulation.h"
#include <ctime>    
#include <cstdlib> 
#include <cmath>
#define	MTIMESEC	300
#define ADJUSTT		60
using namespace std;


Simulation::Simulation(unsigned int fulln, unsigned int spv, unsigned int miners):correctParameters(true),txsPresent(false) {
	/*Me fijo si los parametros son correctos*/
	if (fulln + spv + miners> MAXNODES || miners>fulln) {
		this->correctParameters = false;
	}
	else {
		this->fulln = fulln;
		this->spvn = spv;
		this->minersn = miners+1;
		this->tot = fulln + spvn + minersn+1;
		//creo la matriz de adyacencia
		adjacenceM = new bool*[tot];
		for (int i = 0; i < tot+1; i++) {
			adjacenceM[i] = new bool[tot];
			for (int j = 0; j < tot+1; j++) {
				adjacenceM[i][j] = false;
			}
		}
		Cajita* caj = new Cajita;
		//caj.setFrom(string(""));
		//caj.setTo(string(""));
		//caj.setAmount(string(""));
		cajita.push_back(caj);
		createNetwork();
		startCoinCirculation();
	}
	//vec2arr_nodes();
}


void Simulation::destroySim() {
	for (int i = 0; i < tot; i++) {
		delete n[i];
	}
	delete cajita[0];
}

void Simulation::createNetwork() {
	string id = "node";
	/*creo los nodos Full, Miner y SPV y los guardo*/
	for (int i = 0; i < fulln; i++) {
		Full* node = new Full(id + to_string(i));
		n.push_back(node);
	}

	for (int i = 0; i < minersn; i++) {
		Miner* node = new Miner(id+to_string(i));
		n.push_back(node);
		this->miners.push_back(node);
	}

	Miner* node = new Miner("SatoshiNakamoto");
	this->Satochi = node;
	this->miners.push_back(node);
	n.push_back(node);

	for (int i = 0; i < spvn; i++) {
		SPV* node = new SPV(id + to_string(i + fulln + minersn));
		n.push_back(node);
	}

	//conecto los nodos Full
	connectFulls();

	//me fijo si el grafo es conexo
	connectGraph(n[0], 0);

	//ahora conecto los nodos SPVs
	connectSPVs();
	
}

void Simulation::createTx(string idEmission, string idReceiver, double amount) {
	for (Node* n : n) {
		if (n->getID() == idEmission) {
			n->makeTx(idReceiver, amount);
		}
	}
	this->txsPresent = true;
}

void Simulation::connectFulls() {
	srand(time(0));
	int found;
	string id = "node";

	for (int i = 0; i < fulln + minersn; i++) {
		//el ciclo solo se hace si la cantidad de vecinos es menor que dos
			found = n[i]->getNeighbours().size();
			bool correct = false;
			int r;
			//busco dos nodos que aun no sean vecinos de nodo n[i]
			while (found<2) {
				while (!correct) {
					r = rand() % (fulln + minersn);
					correct = (r != i) && !(n[i]->isNeighbour(id + to_string(r)));
				}
					n[i]->attach(n[r]);
					n[r]->attach(n[i]);
					//actualizo la matriz de adyacencia;
					adjacenceM[i][r] = adjacenceM[r][i]= true;
					found++;
				
			}
		}
}



void Simulation::connectGraph(Node* nodito, int index) {
	//hago bfs a ver si llego al otro nodo
	//primero pongo a todos los nodos como "no visitados"
	for (Node* node : this->n) {
		node->reset();

	}
	//agrego el primero nodo a la cola
	bfsList.push(nodito);
	//hago bfs
	while (!bfsList.empty()) {
		bfsList.front()->visit();
		cout << bfsList.front()->getID() << endl;
		//agarro el primer node de la cola y visito todos sus vecinos y los pongo en la cola
		for (Node* node : bfsList.front()->getNeighbours()) {
			if (!node->wasVisited()) {
				node->visit();
				bfsList.push(node);
			}
		}
		bfsList.pop();
	}

	//si la cantidad de nodos visitados es distinta a la cantidad de nodos, conecto dos partes no conexas
	if(false==allVisited()){
		//busco un nodo que no haya sido visitado y lo conecto con nodito
		bool found = false;
		for (int i = 0; i < this->n.size() && !found; i++) {
			if (!this->n[i]->wasVisited()) {
				nodito->attach(n[i]);
				n[i]->attach(nodito);
				adjacenceM[i][index] = adjacenceM[index][i] = true;
				found = true;
			}
		}
		//vuelvo a llamar a conected para ver si ahora el grafo es conexo
		connectGraph(nodito, index);
	}
}

void Simulation::connectSPVs() {
	srand(time(NULL));
	int j = 0;
	int total = fulln + minersn;
	//por cada nodo SPV elijo al azar nodos Fulls con los cuales conectarlo
	for (int i = total ; i < this->tot-1; i++) {
		for (int k = 0; k < TOTALCONNECTIONS; k++) {
			n[i]->attach(n[j%total]);
			n[j%total]->attach(n[i]);
			adjacenceM[i][j%total] = adjacenceM[j%total][i] = true;
			j++;
		}
	}
}

void Simulation::startCoinCirculation() {
	//creamos la primera transacción y se la mandamos a todos los nodos

	nlohmann::json genesis;
	//deberiamos tener la signature de Satochi
	Input genesisInput("BlockID", to_string(generateIDString("0")),Satochi->getID());
	Output genesisOutPut(Satochi->getID(), 50);
	vector<Input> gi;
	vector<Output> go;
	gi.push_back(genesisInput);
	go.push_back(genesisOutPut);
	Transaction genesisTransaction(gi, go);
	genesisTransaction=Satochi->signTx(genesisTransaction);
	genesis=genesisTransaction.tranformToJson();
	
	ECDSA<ECP, SHA256>::PublicKey pk;
	pk = Satochi->getPk();
	for (int i = 0; i < fulln; i++) {
		Full* f = (Full*)n[i];
		f->receiveTx(genesis, this->Satochi, pk);
	}
	for (int i = 0; i < minersn + fulln; i++) {
		Miner* m = (Miner*)n[i];
		m->receiveTx(genesis, this->Satochi, pk);
	}
}

void Simulation::printMatrix() {
	for (int i = 0; i < this->tot; i++) {
		for (int j = 0; j < this->tot; j++){
			cout << adjacenceM[i][j];
		}
	}
}

bool Simulation::allVisited() {
	for (Node* node : n) {
		if (node->wasVisited()==false) {
			return false;
		}
	}
	return true;
}

void Simulation::keepMining() {
	if (!start) {
		start = clock();
		started = true;
	}
		clock_t end = clock();
		clock_t elapse = end - start;
		bool notMined();
		for (int i = 0; i < this->miners.size(); i++) {
			if (miners[i]->mine()) {
				miners[i]->hasMined();
				for (Miner* m : miners) {
					m->adjustMine(start, end);
				}
				start = false;
				this->txsPresent = false;
			}
		}
}



