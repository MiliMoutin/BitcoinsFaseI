#include "NodeView.h"

void
NodeView::drawNode(Node& nodo)
{
	al_draw_filled_circle(position.px, position.py, RADIO, al_map_rgb(0, 255, 0));
	al_draw_text(font, al_map_rgb(255, 0, 0), position.px, position.py - TEXTSIZE, ALLEGRO_ALIGN_CENTER, nodo.getType().c_str());
	al_flip_display();
	is_drawn = true;
	return;
}

