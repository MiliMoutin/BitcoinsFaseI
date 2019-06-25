#pragma once
#include "Observer.h"
#include "NodeView.h"
#include "Simulation.h"
#include "CajitaView.h"
#include "Allegro.h"

class SimulationView : public Observer
{
public:
	SimulationView(Allegro& alle, int cant);
	~SimulationView();
	virtual void update(void* model);
	ALLEGRO_DISPLAY* get_display() { return display; }

	vector<NodeView> get_node_views() { return nodes; }
private:
	void drawSim(Simulation* sim);//(Node* node_array, Cajita* caja);
	void drawConnections(Simulation*sim);//Node* node_array);
	ALLEGRO_DISPLAY* display;
	CajitaView cajita;
	bool** ady_matrix;  //quien y como se crea?? El update
	vector<NodeView> nodes;
	int cant_nodes;
};