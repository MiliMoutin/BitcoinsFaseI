#pragma once
#include "Controller.h"
#include "Cajita.h"

class CajitaCtrl :public Controller
{
public:
	CajitaCtrl();
	~CajitaCtrl();
	void dispatcher(void*model);
	ALLEGRO_EVENT getEvent();
private:
	ALLEGRO_EVENT_QUEUE* event_queue;
	display_pos pos;
};