#include <iostream>
#include <nlohmann/json.hpp>
#include "Block.h"
#include "MerkleNode.h"
#include "Full.h"
#include <string>
#include <exception>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


using namespace std;

Block createBlock(nlohmann::json block);

int main(void) {

	int size1;
	int size2;
	char* buffer1;
	char* buffer2;

	ifstream blockchainpruebafile("BLOCK.json", ios::binary);

	if (blockchainpruebafile.is_open()) {

		blockchainpruebafile.seekg(0, blockchainpruebafile.end);
		size2 = blockchainpruebafile.tellg();

		buffer2 = new char[size2];
		blockchainpruebafile.seekg(0, ios::beg);
		blockchainpruebafile.read(buffer2, size2);
		blockchainpruebafile.close();
		buffer2[size2] = 0;

		nlohmann::json* block;

		string buf2(buffer2);

		buf2 = buf2.substr(buf2.find_first_of("{"), buf2.find_last_of("}"));

		nlohmann::json b = nlohmann::json::parse(buf2);

		Block blockToSend = createBlock(b);

		SPV n2("nodo2");
		Full gordo1("gordo1");
		Full gordo2("gordo2");

		n2.attach(&gordo1);
		gordo1.attach(&n2);
		n2.attach(&gordo2);
		gordo2.attach(&n2);
		gordo1.setFilter(n2.getId());


		gordo1.injectBlock(blockToSend);
		

	}
	

}

Block createBlock(nlohmann::json block) {
	try {
		//busco las transacciones del bloque 
		unsigned long size = 0;
		vector<Transaction> transactions;
		for (int i = 0; i < block["Txs Count"]; i++) {
			Output output(block["Txs"][i]["Output"]["publicKey"], block["Txs"][i]["Output"]["EDACoins"]);
			Input input(block["Txs"][i]["Input"]["BlockID"], block["Txs"][i]["Input"]["TxID"]);
			Transaction t(input, output);
			string aux = to_string(t.amountOutput()) + to_string(t.getUTXOId()) + t.idReceiver();
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
}
