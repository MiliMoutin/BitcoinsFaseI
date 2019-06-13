#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iterator> 
#include "Transaction.h"
#include "Subject.h"
#include "UTXO.h"

using namespace std;

struct node_pos
{
	int px;
	int py;
};


class Node :public Subject{
public:

	virtual bool isNeighbour(string id) = 0;
	virtual string getType() = 0;
	virtual string getID() = 0;
	virtual void attach(Node* n) = 0;
	virtual list<Node*> getNeighbours() = 0;
	virtual void makeTx(string publicId, double EDACoins);
	void visit() { visited = true; }
	string getPublicID() { return this->publicID; }
	bool wasVisited() { return visited; }
	void reset() { visited = false; }
	void set_position(int x, int y) { position.px = x; position.py = y; return; }
	node_pos get_position() { return position; }
	bool operator==(Node* n);


protected:
	bool canDoTx(double amount);
	list<UTXO> UTXOs;
	list <Node*> neighbours;
	string publicID;
	Transaction to_send;
	string privateID;
	bool visited;
	node_pos position;
};
