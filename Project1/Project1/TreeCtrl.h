#pragma once
#include"Block.h"
#include "AllegroCtrl.h"

class TreeCtrl :public AllegroCtrl
{
public:
	TreeCtrl(ALLEGRO_DISPLAY* display);
	void dispatcher(void* model);
	~TreeCtrl();
};
