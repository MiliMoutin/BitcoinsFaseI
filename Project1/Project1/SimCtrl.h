#pragma once
#include <iostream>
#include "Simulation.h"
#include "AllegroCtrl.h"

using namespace std;

enum state { no_state, from, to, amount };

#define FROM(x) ((x>=30)&&(x<=((DISPLAY_W/3)-30)))
#define TO(x) ((x>=(DISPLAY_W/3) + 30)&&(x<=((DISPLAY_W/3)*2-30)))
#define AMOUNT(x) ((x>=(DISPLAY_W/3)*2 + 30)&&(x<=((DISPLAY_W/3)*3-30)))
#define SEND(x,y) (((x>=((DISPLAY_W / 2) - (TEXTSIZE * 2)))&&(x<=((DISPLAY_W / 2) - (TEXTSIZE * 2))))&&((y >= (DISPLAY_H - (TEXTSIZE * 2))) && (y <= (DISPLAY_H - TEXTSIZE))))


class SimCtrl :public AllegroCtrl 
{
public:
	SimCtrl(ALLEGRO_DISPLAY* display);
	~SimCtrl(){}
	void Alle_dispatcher(void*model, ALLEGRO_EVENT ev);
	state stat;		//estado de la cajita
};