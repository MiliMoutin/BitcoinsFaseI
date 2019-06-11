#pragma once
#include <iostream>
#include "Controller.h"
#include "Simulation.h"

using namespace std;



#define TEXTSIZE 15
#define RADIO TEXTSIZE*2

#define FROM
#define TO
#define AMOUNT

class SimCtrl :public Controller 
{
public:
	SimCtrl(ALLEGRO_DISPLAY* display);
	~SimCtrl();
	void dispatcher(void*model);
	ALLEGRO_EVENT getEvent();
private:
	ALLEGRO_EVENT_QUEUE* event_queue;
	display_pos pos;
};