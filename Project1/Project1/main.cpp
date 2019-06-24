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
	Simulation EDACoin(5,5,3);
	if (EDACoin.creationSuccessful()) {
		cout << "successfull creation" << endl;
	}
	EDACoin.createTx("Satoshi Nakamoto", "nodo1", 10);
	EDACoin.prueba();
	sleep_for(minutes(20));
	return 0;
}

