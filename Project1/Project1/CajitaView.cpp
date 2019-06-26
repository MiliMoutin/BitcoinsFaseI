#include "CajitaView.h"


CajitaView::CajitaView(Allegro& alle)
{
	font = alle.font;
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

	//1. Dibujo el Titulo
	//2. Dibujo un rectangulo blanco, para borrar lo que ya habia
	//3. Recuadro el "cuadro de texto"
	//4. Escribo lo que corresponde
	al_draw_text(font, al_map_rgb(0, 255, 0), 30, (C_DISPLAY_H / 2) - TEXTSIZE + N_DISPLAY_H, ALLEGRO_ALIGN_LEFT, "From:");
	al_draw_filled_rectangle(30, (C_DISPLAY_H / 2) + N_DISPLAY_H, x - 30, (C_DISPLAY_H / 2) + TEXTSIZE*2 + N_DISPLAY_H, al_map_rgb(255, 255, 255));
	al_draw_rectangle(30, (C_DISPLAY_H / 2) + N_DISPLAY_H, x-30, (C_DISPLAY_H / 2) + TEXTSIZE + N_DISPLAY_H, al_map_rgb(0, 0, 0), 1);
	al_draw_text(font, al_map_rgb(0, 0, 255), 30, (C_DISPLAY_H / 2) + N_DISPLAY_H, ALLEGRO_ALIGN_LEFT, caja->getFrom().c_str());

	al_draw_text(font, al_map_rgb(0, 255, 0), x+30, (C_DISPLAY_H / 2) - TEXTSIZE + N_DISPLAY_H, ALLEGRO_ALIGN_LEFT, "To:");
	al_draw_filled_rectangle(x + 30, (C_DISPLAY_H / 2) + N_DISPLAY_H, x * 2 - 30, (C_DISPLAY_H / 2) + TEXTSIZE*2 + N_DISPLAY_H, al_map_rgb(255, 255, 255));
	al_draw_rectangle(x+30, (C_DISPLAY_H / 2) + N_DISPLAY_H, x*2-30, (C_DISPLAY_H / 2) + TEXTSIZE + N_DISPLAY_H, al_map_rgb(0, 0, 0), 1);
	al_draw_text(font, al_map_rgb(0, 0, 255), x + 30, (C_DISPLAY_H / 2) + N_DISPLAY_H, ALLEGRO_ALIGN_LEFT, caja->getTo().c_str());

	al_draw_text(font, al_map_rgb(0, 255, 0), x*2+30, (C_DISPLAY_H / 2) - TEXTSIZE + N_DISPLAY_H, ALLEGRO_ALIGN_LEFT, "Amount:");
	al_draw_filled_rectangle(x * 2 + 30, (C_DISPLAY_H / 2) + N_DISPLAY_H, x * 3 - 30, (C_DISPLAY_H / 2) + TEXTSIZE*2 + N_DISPLAY_H, al_map_rgb(255, 255, 255));
	al_draw_rectangle(x*2+30, (C_DISPLAY_H / 2) + N_DISPLAY_H, x*3-30, (C_DISPLAY_H / 2) + TEXTSIZE + N_DISPLAY_H, al_map_rgb(0, 0, 0), 1);
	al_draw_text(font, al_map_rgb(0, 0, 255), x*2 + 30, (C_DISPLAY_H / 2) + N_DISPLAY_H, ALLEGRO_ALIGN_LEFT, caja->getAmount().c_str());

	al_draw_text(font, al_map_rgb(0, 255, 0), (DISPLAY_W/2) - (TEXTSIZE*2), DISPLAY_H - (TEXTSIZE * 2), ALLEGRO_ALIGN_LEFT, "SEND");
	al_draw_rectangle((DISPLAY_W / 2) - (TEXTSIZE * 2), DISPLAY_H-(TEXTSIZE*2), (DISPLAY_W / 2) + (TEXTSIZE * 2), DISPLAY_H - TEXTSIZE, al_map_rgb(0, 0, 0), 1);
	
	al_flip_display();
}