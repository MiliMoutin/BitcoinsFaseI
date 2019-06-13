#pragma once
#include <vector>
#include "SPV.h"
#include "GenerateID.h"
#include "Path.h"
#include "MerkleNode.h"
#include "MerkleRoot.h"
#include "HeaderBlock.h"
#include "Block.h"
#include "SPV.h"

#define LEFT true
#define RIGHT false

class SPV;

class Full :public Node {

public:
	Full() {}
	Full(string id);
	string getType() { return "Full"; }
	virtual string getID() { return this->id; }
	void attach(Node* n);
	void setFilter(string id);
	virtual void makeTx(string publicId, double EDACoins);
	bool emptyBlockchain() { return blockchain.empty(); }
	HeaderBlock askForHeader() { return this->blockchain.back().getHeader(); }
	void injectBlock(Block b);
	void destroy() { destroyBlockchain(); }
	bool isNeighbour(string id);
	virtual void receiveTx(nlohmann::json tx, Node* n);

	list<Block> getBchain() { return blockchain; }
	list<Node*> getNeighbours() { return neighbours; }
protected:
	//si llega un bloque y aparece alguno de los filters el node avisa
	vector<string> filters;
	list<Block> blockchain;
	string id;
	vector<MerkleRoot*> merkleroots;
	vector<Transaction> receivedTx;

	void destroyBlockchain();
	void destroyTree(MerkleNode* nd);

	//crea arbol a partir de la llegada de un nuevo bloque
	MerkleNode* createTreeRec(int cantCicle, vector<Transaction> Txsvec, int* index);
	MerkleRoot* createTree(Block b);

	//busca si dentro de un bloque hay transacciones de mi filtro
	bool SearchForFilterTransactions(Block b, string id);

	//funciones para armar el path
	Path getPath(MerkleRoot* mr, unsigned long id);
	bool searchPathRec(MerkleNode* n, Path& path, unsigned long i, bool& found);

	//armo el EDAMerkleBlock para mandarle a mi neighbour
	EDAMerkleBlock getTreeInfo(string id);//devuelve los paths a las transacciones necesarias

	//funciones auxiliares para usar el arbol
	//devuelve el vector de transacciones que voy a usar como hojas
	vector<Transaction> createVectorForTree(vector<Transaction> initial, int* height);
	//devuelve si un numero es cuadrado perfecto
	bool isPot2(int cant, int* exponent);

	Transaction transformJStoTx(nlohmann::json tx);

	void communicateTx(nlohmann::json tx);

	bool checkUTXOinBlockchain(unsigned long id);



};
