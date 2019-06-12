#include "NodeView.h"


void
NodeView::update(void* model)
{
	Node* n = (Node*)model;
	drawNode(n);
}


NodeView::NodeView(Allegro& alle)
{
	font = alle.font;
}


void
NodeView::drawNode(Node* nodo)
{
	al_draw_filled_circle(nodo->get_position().px, nodo->get_position().py, RADIO, al_map_rgb(0, 255, 0));
	al_draw_text(font, al_map_rgb(255, 0, 0), nodo->get_position().px, nodo->get_position().py - TEXTSIZE, ALLEGRO_ALIGN_CENTER, nodo->getType().c_str());
	al_draw_text(font, al_map_rgb(255, 0, 0), nodo->get_position().px, nodo->get_position().py, ALLEGRO_ALIGN_CENTER, nodo->getID().c_str());
	al_flip_display();
	is_drawn = true;
	return;
}

