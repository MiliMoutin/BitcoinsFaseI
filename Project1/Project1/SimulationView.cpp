#include "SimulationView.h"
#define _USE_MATH_DEFINES
#include <math.h>

SimulationView::SimulationView(Allegro& alle):cajita(alle)
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

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB
	al_flip_display();
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
	for (int i = 0; i < cant_nodes; i++)
	{
		for (int a = 0; a < cant_nodes; a++)
		{
			ady_matrix[i][a] = sim->get_adyM()[i][a];
		}

	}
	al_clear_to_color(al_map_rgb(255, 255, 255));
	drawSim(sim->get_nodes(), &(sim->get_cajita()));
	return;
}


void
SimulationView::drawSim(Node* node_array, Cajita* caja)
{
	int dif = 360 / cant_nodes;
	double rad_dif = (dif * 2 * M_PI) / 360;

	for (int i = 0; i < cant_nodes; i++)
	{
		node_array[i].set_position(N_DISPLAY_W/2 + GRAPH_RADIUS*cos(rad_dif*(i)), N_DISPLAY_H/2 + GRAPH_RADIUS*sin(rad_dif*(i)));
	}
	drawConnections(node_array);

	for (int i = 0; i < cant_nodes; i++)
	{
		nodes[i].drawNode(&(node_array[i]));
	}
	
	cajita.drawCajita(caja);
}

void
SimulationView::drawConnections(Node* nodes)
{
	for (int i = 0; i < cant_nodes; i++)
	{
		for (int a = i; a < cant_nodes; a++)
		{
			if (ady_matrix[i][a])
			{
				al_draw_line(nodes[i].get_position().px, nodes[i].get_position().py, nodes[a].get_position().px, nodes[a].get_position().py, al_map_rgb(255, 255, 255), 0);
			}
		}
	}
	al_flip_display();
}
