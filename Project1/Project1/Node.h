#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iterator> 

using namespace std;

class Node {
public:
	virtual string getType() = 0;
	virtual string getID() = 0;
	virtual void attach(Node* n) = 0;
};
