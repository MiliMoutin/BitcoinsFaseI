#include <iostream>
#include <nlohmann/json.hpp>
#include "Block.h"
#include "MerkleNode.h"
#include "Full.h"
#include "Allegro.h"
#include "Simulation.h"
#include "SimulationView.h"
#include <string>
#include <exception>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


using namespace std;


int main(void) {
	Allegro alle;
	Simulation EDACoin(5,5,3);
	SimulationView vi(alle, EDACoin.get_total()-1);
	EDACoin.attach(vi);
	EDACoin.notifyAllObservers();
	if (EDACoin.creationSuccessful()) {
		cout << "successfull creation" << endl;

		//EDACoin.createTx("Satoshi Nakamoto", "nodo1", 10);
		//EDACoin.prueba();
	}
	getchar();
	return 0;
}

