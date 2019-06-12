#pragma once
#include "Observer.h"
#include "NodeView.h"
#include "Simulation.h"
#include "CajitaView.h"
/*
#define N_DISPLAY_W 700
#define N_DISPLAY_H 700
#define GRAPH_RADIUS ((N_DISPLAY_W/2)-30)

#define C_DISPLAY_W N_DISPLAY_W
#define C_DISPLAY_H 200

#define DISPLAY_W N_DISPLAY_W
#define DISPLAY_H (N_DISPLAY_H + C_DISPLAY_H)


#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15
*/
class SimulationView : public Observer
{
public:
	SimulationView();
	~SimulationView();
	virtual void update(void* model);
	ALLEGRO_DISPLAY* get_display() { return display; }
/*protected:
	ALLEGRO_FONT* font;*/
private:
	void drawSim(Node* node_array, Cajita* caja);
	void drawConnections(Node* node_array);
	ALLEGRO_DISPLAY* display;
	CajitaView cajita;
	bool** ady_matrix;  //quien y como se crea?? El update
	//list<NodeView> nodes;
	NodeView* nodes;
	int cant_nodes;
};