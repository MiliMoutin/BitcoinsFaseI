#include "SimulationView.h"
#define _USE_MATH_DEFINES
#include <math.h>

void
SimulationView::update(void* model)
{
	Simulation* sim = (Simulation*)model;
	drawSim(sim->get_nodes());
	return;
}


void
SimulationView::drawSim(Node* node_array)
{
	int dif = 360 / cant_nodes;
	double rad_dif = (dif * 2 * M_PI) / 360;

	for (int i = 0; i < cant_nodes; i++)
	{
		nodes[i].set_position(N_DISPLAY_W/2 + GRAPH_RADIUS*cos(rad_dif*(i)), N_DISPLAY_H/2 + GRAPH_RADIUS*sin(rad_dif*(i)));
	}
	drawConnections();

	for (int i = 0; i < cant_nodes; i++)
	{
		nodes[i].drawNode(node_array[i]);
	}

	//drawCajita o cajita.update
}

void
SimulationView::drawConnections()
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