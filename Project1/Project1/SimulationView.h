#pragma once
#include "Observer.h"
#include "NodeView.h"
#include "Simulation.h"
#include "CajitaView.h"


class SimulationView : public Observer
{
public:
	void update(void* model);
protected:
	ALLEGRO_FONT* font;
private:
	void drawSim(Node* node_array);
	void drawConnections();
	ALLEGRO_DISPLAY* display;
	CajitaView cajita;
	bool** ady_matrix;  //quien y como se crea??
	NodeView* nodes;
	int cant_nodes;
};