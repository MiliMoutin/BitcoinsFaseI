#pragma once
#include "Controller.h"
#include "Allegro.h"




class AllegroCtrl :public Controller
{
public:
	AllegroCtrl();
	~AllegroCtrl();
	virtual void dispatcher(void* model) = 0;
	ALLEGRO_EVENT getEvent();		//devuelve el proximo evento
	ALLEGRO_EVENT_QUEUE* event_queue;
	display_pos pos;
	int page;
};