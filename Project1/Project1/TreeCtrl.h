#pragma once
#include "Controller.h"
#include"Block.h"
#include "AllegroCtrl.h"

class TreeCtrl :public AllegroCtrl
{
public:
	TreeCtrl(ALLEGRO_DISPLAY* display);
	//ALLEGRO_EVENT getEvent();
	void dispatcher(void* model);
	~TreeCtrl();
/*private:
	ALLEGRO_EVENT_QUEUE* event_queue;*/
};
