#include <iostream>
#include <nlohmann/json.hpp>
#include "Block.h"
#include "Full.h"
#include <string>
#include <exception>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


using namespace std;

MerkleNode* createMerkleTree(nlohmann::json j);
Block createBlock(nlohmann::json merkletree, nlohmann::json block);

int main(void) {

	int size1;
	int size2;
	char* buffer1;
	char* buffer2;

	ifstream merkletreefile("MT.json", ios::in | ios::binary);
	ifstream blockchainpruebafile("BLOCK.json", ios::binary);

	if (merkletreefile.is_open() && blockchainpruebafile.is_open())
	{
		merkletreefile.seekg(0, merkletreefile.end);
		size1 = merkletreefile.tellg();

		buffer1 = new char[size1];
		merkletreefile.seekg(0, ios::beg);
		merkletreefile.read(buffer1, size1);
		merkletreefile.close();
		buffer1[size1] = 0;

		blockchainpruebafile.seekg(0, blockchainpruebafile.end);
		size2 = blockchainpruebafile.tellg();

		buffer2 = new char[size2];
		blockchainpruebafile.seekg(0, ios::beg);
		blockchainpruebafile.read(buffer2, size2);
		blockchainpruebafile.close();
		buffer2[size2] = 0;

		nlohmann::json* merkletree;
		nlohmann::json* block;

		string buf1(buffer1);
		string buf2(buffer2);

		buf2 = buf2.substr(buf2.find_first_of("{"), buf2.find_last_of("}"));
		buf1 = buf1.substr(buf1.find_first_of("{"), buf1.find_last_of("}"));

		/*Full f1("GrandotaWachin");
		Full f2("Gordo");
		SPV f3("nodo2");*/

		nlohmann::json mt = nlohmann::json::parse(buf1);
		nlohmann::json b = nlohmann::json::parse(buf2);

		Block blockToSend = createBlock(mt, b);
		cout << "daleIngrid";
		cout << blockToSend.getCantTxs() << endl;
		cout << blockToSend.getId() << endl;
		sleep_for(minutes(10));

	}

}

Block createBlock(nlohmann::json merkletree, nlohmann::json block) {
	//busco las transacciones del bloque 
	try {
		cout << "llego";
		unsigned long size = 0;
		vector<Transaction> transactions;
		cout << block["Txs Count"] << endl << endl;
		for (int i = 0; i < block["Txs Count"]; i++) {
			Output output(block["Txs"][i]["Output"]["publicKey"], block["Txs"][i]["Output"]["EDACoins"]);
			Input input(block["Txs"][i]["Input"]["BlockID"], block["Txs"][i]["Input"]["TxID"]);
			Transaction t(input, output);
			transactions.push_back(t);
		}

		//busco y guardo el ID del bloque
		cout << merkletree["ID"] << endl;
		unsigned long id = merkletree["ID"];

		//creo la root de Merkle tree y lo lleno usando la funcion create MerkleTree
		MerkleRoot root(id);
		cout << merkletree["nodes"][0] << endl;
		cout << merkletree["nodes"][1] << endl;
		root.setFirstChildren(createMerkleTree(merkletree["nodes"][0]), createMerkleTree(merkletree["nodes"][1]));

		//creo el bloque
		Block newblock(transactions, root, block["BlockID"]);

		return newblock;
	}
	catch (exception& e) {
		cout << e.what();
	}
}

MerkleNode* createMerkleTree(nlohmann::json j) {
	//si es una hoja mando el node solo
	if (j["nodes"].empty()) {
		MerkleNode* node = new MerkleNode(j["ID"]);
		return node;
	}
	//si no es una hoja vuelvo a llamar a la funcion para crear los hijos
	else {
		MerkleNode* node = new MerkleNode(j["ID"]);
		if (j["nodes"].size() == 1) {
			node->setLeft(createMerkleTree(j["nodes"][0]));
		}
		else {
			node->setRight(createMerkleTree(j["nodes"][1]));
		}
		return node;
	}
}

