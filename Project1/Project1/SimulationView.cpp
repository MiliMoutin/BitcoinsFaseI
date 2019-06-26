#include "SimulationView.h"
#define _USE_MATH_DEFINES
#include <math.h>

SimulationView::SimulationView(Allegro& alle, int cant):cajitav(alle)
{
	int w = C_DISPLAY_W;
	int h = N_DISPLAY_H+C_DISPLAY_H;

	display = al_create_display(w, h); // Intenta crear display de fallar devuelve NULL

	if (!display)
	{
		cout << "failed to create display!\n";
		return;
	}

	al_init_primitives_addon();

	al_set_window_position(display, 0, 0);
	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB
	al_flip_display();

	for (int i = 0; i < cant; i++)
	{
		nodes.push_back(NodeView(alle));
	}
}

SimulationView::~SimulationView()
{
	al_destroy_display(display);
}

void
SimulationView::update(void* model)
{
	Simulation* sim = (Simulation*)model;
	cant_nodes = sim->get_total();
	


	al_clear_to_color(al_map_rgb(255, 255, 255));
	drawSim(sim);//->get_nodes(), &(sim->get_cajita()));
	return;
}


void
SimulationView::drawSim(Simulation* sim)//(Node* node_array, Cajita* caja)
{
	int dif = 360 / cant_nodes;
	double rad_dif = (dif * 2 * M_PI) / 360;

	for (int i = 0; i < cant_nodes; i++)
	{
		sim->get_nodes()[i]->set_position(N_DISPLAY_W/2 + GRAPH_RADIUS*cos(rad_dif*(i)), N_DISPLAY_H/2 + GRAPH_RADIUS*sin(rad_dif*(i)));
	}
	drawConnections(sim);

	for (int i = 0; i < cant_nodes; i++)
	{
		nodes[i].drawNode(sim->get_nodes()[i]);
	}
	
	cajitav.drawCajita(sim->get_cajita()[0]);
}

void
SimulationView::drawConnections(Simulation* sim)
{
	for (int i = 0; i < cant_nodes; i++)
	{
		for (int a = i; a < cant_nodes; a++)
		{
			if (sim->get_adyM()[i][a])
			{
				al_draw_line(sim->get_nodes()[i]->get_position().px, sim->get_nodes()[i]->get_position().py, sim->get_nodes()[a]->get_position().px, sim->get_nodes()[a]->get_position().py, al_map_rgb(0, 0, 0), 0);
			}
		}
	}
	al_flip_display();
}
