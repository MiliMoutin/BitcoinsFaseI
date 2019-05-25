#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iterator> 

using namespace std;

class Node {
public:
	virtual bool attach(Node n);
	virtual string getType();
	virtual string getId();
	virtual void getFilter();

protected:
	string type;
	string id;
	list <Node> neighbours;
};
