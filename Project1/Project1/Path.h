#pragma once
#include <iostream>
#include <vector>
#include "PathElement.h"
#include "nlohmann/json.hpp"

using namespace std;

class Path {
public:
	Path(){}
	//true es left, false es right
	Path(nlohmann::json j) {
		for (int i = 0; i < j.size(); i++) {
			this->ids.push_back(PathElement(j[i]));
		}
	}
	void addID(string id, bool lof) { ids.push_back(PathElement(id,lof)) ; }
	vector<PathElement> getPath() { return this->ids; }
	nlohmann::json TransformToJson() { nlohmann::json j;
	for(int i=0; i< ids.size(); i++){
		j[i] = ids[i].TransformToJson();
		}
	return j;
	}
private:
	vector<PathElement> ids;
};