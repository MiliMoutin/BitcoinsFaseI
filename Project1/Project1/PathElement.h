#pragma once
#include "nlohmann/json.hpp"


class PathElement {
public:
	//true es left, false es right
	PathElement(string id, bool lof) {
		this->id = id;
		this->lof = lof;
	}
	PathElement(nlohmann::json j) { string id = j["id"]; bool b = j["lof"]; this->id = id; lof = b; }
	bool getLoF() { return lof; }
	string getId() { return id; }
	nlohmann::json TransformToJson() { nlohmann::json j; j["id"] = id; j["lof"] = lof;  return j; }

private:
	string id;
	bool lof;
};
