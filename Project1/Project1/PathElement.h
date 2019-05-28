#pragma once

class PathElement {
public:
	//true es left, false es right
	PathElement(unsigned long id, bool lof) {
		this->id = id;
		this->lof = lof;
	}
	bool getLoF() { return lof; }
	unsigned long getId() { return id; }
private:
	unsigned long id;
	bool lof;
};
