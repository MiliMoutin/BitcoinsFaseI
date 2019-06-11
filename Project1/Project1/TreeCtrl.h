#pragma once
#include "Controller.h"
#include"Block.h"

class TreeCtrl :public Controller
{
public:
	TreeCtrl(ALLEGRO_DISPLAY* display);
	ALLEGRO_EVENT getEvent();
	void dispatcher(void* model);
	~TreeCtrl();
private:
	ALLEGRO_EVENT_QUEUE* event_queue;
};
