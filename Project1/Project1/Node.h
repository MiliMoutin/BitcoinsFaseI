#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iterator> 
#include "Subject.h"

using namespace std;

class Node :public Subject{
public:
	virtual bool isNeighbour(string id) = 0;
	virtual string getType() = 0;
	virtual string getID() = 0;
	virtual void attach(Node* n) = 0;
	virtual list<Node*> getNeighbours() = 0;
	void visit() { visited = true; }
	bool wasVisited() { return visited; }
	void reset() { visited = false; }
private:
	bool visited;
};
