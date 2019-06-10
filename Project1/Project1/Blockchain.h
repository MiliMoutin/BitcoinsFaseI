#pragma once
#include "Subject.h"
#include "Block.h"

class Blockchain :public Subject 
{
public:
	list<Block> getBchain() { return bchain; }
private:
	list<Block> bchain;
};