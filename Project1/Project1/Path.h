#pragma once
#include <iostream>
#include <vector>
#include "PathElement.h"

using namespace std;

class Path {
public:
	Path(){}
	//true es left, false es right
	void addID(unsigned long id, bool lof) { ids.push_back(PathElement(id,lof)) ; }
	vector<PathElement> getPath() { return this->ids; }
private:
	vector<PathElement> ids;
};