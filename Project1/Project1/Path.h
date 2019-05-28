#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Path {
public:
	Path(){}
	void addID(unsigned long id) { ids.push_back(id); }
	vector<unsigned long> getPath() { return this->ids; }
private:
	vector<unsigned long> ids;
};