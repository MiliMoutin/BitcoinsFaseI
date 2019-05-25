#include <iostream>
#include<list>
#include "Block.h"
#include "Alllegro.h"

using namespace std;

Allegro::Allegro(unsigned int w, unsigned int h)
{
	display_w = w;
	display_h = h;
	if (!al_init()) 
	{ //Primera funcion a llamar antes de empezar a usar allegro.
		fprintf(stderr, "failed to initialize allegro!\n");
		init_ok = false;
		return;
	}

	if (!al_install_mouse()) 
	{//initialize mouse.
		fprintf(stderr, "failed to initialize the mouse!\n");
		init_ok = false;
		return;
	}

	event_queue = al_create_event_queue();//create event queue.
	if (!event_queue) 
	{
		fprintf(stderr, "failed to create event_queue!\n");
		init_ok = false;
		return;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	font = al_load_ttf_font(TEXTFONT, TEXTSIZE, 0); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :( 
	if (!font) 
	{
		fprintf(stderr, "Could not load text font.\n");
		al_destroy_event_queue(event_queue);
		return;
	}

	display = al_create_display(w, h); // Intenta crear display de fallar devuelve NULL

	if (!display) 
	{
		fprintf(stderr, "failed to create display!\n");
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		init_ok = false;
		return;
	}
	al_init_image_addon();

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)

	//Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola a medida que vayan sucediendo
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO
	al_register_event_source(event_queue, al_get_mouse_event_source()); //REGISTRAMOS EL MOUSE
	init_ok = true;
	return;
}


al_event 
Allegro::getNextEvent(void)
{
	ALLEGRO_EVENT ev;
	al_get_next_event(event_queue, &ev);
	switch (ev.type)
	{
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
	{
		return ev_quit;
		break;
	}
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	{
		pos.x = ev.mouse.x;
		pos.y = ev.mouse.y;
		return ev_mouse;
		break;
	}
	default:
	{
		return ev_null;
		break;
	}
	}
}


unsigned int 
Allegro::GetDisplayW()
{
	return display_w;
}


unsigned int 
Allegro::GetDisplayH()
{
	return display_h;
}


display_pos 
Allegro::GetMousePos()
{
	return pos;
}

void
Allegro::DrawBlock(Block& bloque)
{

}

bool ShowAlle(list<Block>& blockchain)
{
	Allegro alle;
	if (!alle.initAllegro_ok())
	{
		cout << "No se pudo inicializar Allegro" << endl;
		return false;
	}


}