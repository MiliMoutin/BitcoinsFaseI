#include <iostream>
#include <nlohmann/json.hpp>
#include "Block.h"
#include "MerkleNode.h"
#include "Full.h"
#include "Allegro.h"
#include "Simulation.h"
#include "SimulationView.h"
//#include "SimController.h"
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


/*Block createBlock(nlohmann::json block) {
	try {
		//busco las transacciones del bloque 
		unsigned long size = 0;
		vector<Transaction> transactions;
		for (int i = 0; i < block["Txs"].size(); i++) {
			string aux = "";
			vector<Input> input;
			vector<Output> output;
			for (int j = 0; j < block["Txs"][i]["Output"].size(); j++) {
				Output o(block["Txs"][i]["Output"][j]["publicKey"], block["Txs"][i]["Output"][j]["EDACoins"]);
				output.push_back(o);
				aux += to_string(o.getAmount())+ o.getIdReceiver();
				
			}
			for (int j = 0; j < block["Txs"][i]["Output"].size(); j++) {
				Input i(block["Txs"][i]["Input"][j]["BlockID"], block["Txs"][i]["Input"][j]["TxID"]);
				input.push_back(i);
				aux += to_string(i.getBlockID()) + to_string(i.getUTXOId());
			}		
			Transaction t(input, output);
			t.setId(generateIDString(aux));
			transactions.push_back(t);
		}

		//busco y guardo el ID del bloque
		unsigned long id = block["BlockID"];

		return Block(transactions, id);
	}
	catch (exception&e) {
		cout << e.what();
	}
}*/
