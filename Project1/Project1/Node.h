#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iterator> 

using namespace std;

class Node {
public:
	virtual string getType();
	virtual string getId();

protected:
	string type;
	string id;
};
