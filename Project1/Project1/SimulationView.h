#pragma once
#include "Observer.h"
#include "NodeView.h"
#include "Simulation.h"
#include "CajitaView.h"

#define N_DISPLAY_W 700
#define N_DISPLAY_H 700
#define GRAPH_RADIUS ((N_DISPLAY_W/2)-30)

#define C_DISPLAY_W N_DISPLAY_W
#define C_DISPLAY_H 200

#define DISPLAY_W N_DISPLAY_W
#define DISPLAY_H (N_DISPLAY_H + C_DISPLAY_H)


#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15

class SimulationView : public Observer
{
public:
	SimulationView();
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