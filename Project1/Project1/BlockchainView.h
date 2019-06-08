#pragma once
#include "BlockView.h"
#include "allegro5/allegro.h"
#include <list>

class BlockchainView : public Observer
{
public:
	void update(void* model);
private:
	ALLEGRO_DISPLAY* display;
	list<BlockView*> b_chain;
};