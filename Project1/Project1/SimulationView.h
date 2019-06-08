#pragma once
#include <allegro5/allegro.h>
#include "Observer.h"
#include "NodeView.h"

class SimulationView : public Observer
{
public:
	void drawSim();
private:
	ALLEGRO_DISPLAY* display;
	NodeView* nodes;
	//CajitaView cajita;
	bool* ady_matrix;
};