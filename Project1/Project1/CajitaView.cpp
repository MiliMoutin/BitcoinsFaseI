#include "CajitaView.h"


CajitaView::CajitaView()
{
	font = al_load_ttf_font(TEXTFONT, TEXTSIZE, 0);
	if (!font)
	{
		cout << "Could not load text font.\n";
		return;
	}
}

CajitaView::~CajitaView()
{
	al_destroy_font(font);
}


void
CajitaView::update(void* model)
{
	Cajita* caja = (Cajita*)model;
	drawCajita(caja);
	return;
}


void
CajitaView::drawCajita(Cajita* caja)
{
	int x = (DISPLAY_W / 3);
	al_draw_rectangle(0, N_DISPLAY_H, DISPLAY_W, DISPLAY_H, al_map_rgb(0, 0, 0), 2);

	al_draw_text(font, al_map_rgb(0, 255, 0), 30, (C_DISPLAY_H / 2) - TEXTSIZE, ALLEGRO_ALIGN_LEFT, "From:");
	al_draw_rectangle(30, C_DISPLAY_H / 2, x-30, C_DISPLAY_H / 2 + TEXTSIZE, al_map_rgb(0, 0, 0), 1);

	al_draw_text(font, al_map_rgb(0, 255, 0), x+30, (C_DISPLAY_H / 2) - TEXTSIZE, ALLEGRO_ALIGN_LEFT, "To:");
	al_draw_rectangle(x+30, C_DISPLAY_H / 2, x*2-30, C_DISPLAY_H / 2 + TEXTSIZE, al_map_rgb(0, 0, 0), 1);

	al_draw_text(font, al_map_rgb(0, 255, 0), x*2+30, (C_DISPLAY_H / 2) - TEXTSIZE, ALLEGRO_ALIGN_LEFT, "Amount:");
	al_draw_rectangle(x*2+30, C_DISPLAY_H / 2, x*3-30, C_DISPLAY_H / 2 + TEXTSIZE, al_map_rgb(0, 0, 0), 1);

	//FALTA EL SEND
	al_flip_display();
}