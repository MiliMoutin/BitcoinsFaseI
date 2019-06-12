#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iterator> 
#include "Subject.h"

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
	void visit() { visited = true; }
	bool wasVisited() { return visited; }
	void reset() { visited = false; }
	void set_position(int x, int y) { position.px = x; position.py = y; return; }
	node_pos get_position() { return position; }

private:
	bool visited;
	node_pos position;
};
