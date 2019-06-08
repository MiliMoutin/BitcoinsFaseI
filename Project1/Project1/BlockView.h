#pragma once
#include "Observer.h"
#include <string>

using namespace std;

class BlockView //: public Observer
{
public:
	void drawBlock();
private:

	string id;
	int cantTxs;
};