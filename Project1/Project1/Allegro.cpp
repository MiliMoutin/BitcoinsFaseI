#include <iostream>
#include<list>
#include <string>
#include "Block.h"
#include "Allegro.h"

using namespace std;

Allegro::Allegro(unsigned int w, unsigned int h)
{
	display_w = w;
	display_h = h;
	if (!al_init()) 
	{ //Primera funcion a llamar antes de empezar a usar allegro.
		cout<<"failed to initialize allegro!\n";
		init_ok = false;
		return;
	}

	if (!al_install_mouse()) 
	{//initialize mouse.
		cout<<"failed to initialize the mouse!\n";
		init_ok = false;
		return;
	}

	event_queue = al_create_event_queue();//create event queue.
	if (!event_queue) 
	{
		cout<<"failed to create event_queue!\n";
		init_ok = false;
		return;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	font = al_load_ttf_font(TEXTFONT, TEXTSIZE, 0); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :( 
	if (!font) 
	{
		cout<<"Could not load text font.\n";
		al_destroy_event_queue(event_queue);
		return;
	}

	display = al_create_display(w, h); // Intenta crear display de fallar devuelve NULL

	if (!display) 
	{
		cout<<"failed to create display!\n";
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		init_ok = false;
		return;
	}
	al_init_image_addon();

	block_img = al_load_bitmap(BLOCK_IMAGE);
	if (!block_img)
	{
		cout << "failed to load bitmap\n";
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_display(display);
		init_ok = false;
		return;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)

	//Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola a medida que vayan sucediendo
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
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


bool
Allegro::initAllegro_ok()
{
	return init_ok;
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
Allegro::DrawBlock(Block& bloque, int x, int y, int w, int h)
{
	al_draw_scaled_bitmap(block_img, 0, 0, al_get_bitmap_width(block_img), al_get_bitmap_height(block_img), x, y, w, h, 0);

	string id = to_string(bloque.getId());
	string cantx = to_string(bloque.getCantTxs());
	string aux1("ID: " + id);
	string aux2("Txs: " + cantx);
	al_draw_text(font, al_map_rgb(255, 0, 0), x, y + 10, 0, aux1.c_str());
	al_draw_text(font, al_map_rgb(255, 0, 0), x, y + TEXTSIZE, 0, aux2.c_str());
	return;
}

bool ShowAlle(list<Block>& blockchain)
{
	Allegro alle;
	ALLEGRO_BITMAP* r_arrow = al_load_bitmap(ARROW_RIGHT_IMAGE);
	if (!alle.initAllegro_ok())
	{
		cout << "No se pudo inicializar Allegro" << endl;
		return false;
	}

	int posx = 30;
	int posy = 30;
	list<Block>::iterator itr = blockchain.begin();

	if (blockchain.size() > 9)
	{
		al_draw_bitmap(r_arrow, DISPLAY_W, DISPLAY_H, ALLEGRO_ALIGN_RIGHT);
	}

	
	for (; itr != blockchain.end(); ++itr)
	{
		for (; posy >= DISPLAY_H; posy += (IMAGE_H + 30))
		{
			for (; posx >= DISPLAY_W; posx += (IMAGE_W + 30))
			{
				alle.DrawBlock(*itr, posx, posy, IMAGE_W, IMAGE_H);
			}
		}
	}


}