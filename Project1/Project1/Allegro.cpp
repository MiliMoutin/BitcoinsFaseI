#include <iostream>
#include<list>
#include <string>
#include "Block.h"
#include "Allegro.h"

int findTreeH(MerkleRoot* root);

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

	right= al_load_bitmap(ARROW_RIGHT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_display(display);
		al_destroy_bitmap(right);
		init_ok = false;
		return;
	}

	left = al_load_bitmap(ARROW_LEFT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_display(display);
		al_destroy_bitmap(right);
		al_destroy_bitmap(left);
		init_ok = false;
		return;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)

	//Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola a medida que vayan sucediendo
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
	al_register_event_source(event_queue, al_get_mouse_event_source()); //REGISTRAMOS EL MOUSE
	init_ok = true;
	cout << "in allegro" << endl;
	return;
}


Allegro::~Allegro()
{
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_bitmap(block_img);
	al_destroy_bitmap(right);
	al_destroy_bitmap(left);
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


bool 
Allegro::ShowAlle(list<Block>& blockchain)
{
	if (!init_ok)
	{
		cout<<"Allegro failed" << endl;
		return false;
	}
	if (blockchain.size() == 0)
	{
		cout << "Blockchain empty." << endl;
		al_draw_text(font, al_map_rgb(255, 0, 0), DISPLAY_W/2, DISPLAY_H/2, ALLEGRO_ALIGN_CENTER, "Blockchain empty.");
		al_flip_display();
		al_rest(3.0);
		return false;
	}

	NextPage(blockchain);
	/*
	int posx = 30;
	int posy = 30;
	list<Block>::iterator itr = blockchain.begin();
	if (blockchain.size() > 9)
	{
		al_draw_bitmap(right, DISPLAY_W, DISPLAY_H, ALLEGRO_ALIGN_RIGHT);
	}

	
	
	for (; posy <= (DISPLAY_H-IMAGE_H); posy += (IMAGE_H + 30))
	{
		for (; posx <= (DISPLAY_W-IMAGE_W); posx += (IMAGE_W + 30))
		{
			if (itr != blockchain.end())
			{
				DrawBlock(*itr, posx, posy, IMAGE_W, IMAGE_H);
				++itr;
			}
		}
	}
	

	al_flip_display();
	int ev;
	do
	{
		ev = getNextEvent();
		if (ev == ev_mouse)
		{
			mouse_dispatcher(blockchain, blockchain.size());
		}
		
	} while (ev != ev_quit);
	*/
	return true;
}

void 
Allegro::mouse_dispatcher(list<Block>& blockchain, int page)
{
	int size = (blockchain.size() - (9 * (page - 1)));
	list<Block>::iterator itr = blockchain.begin();
	if (pos.x <= DISPLAY_W && pos.y <= DISPLAY_H)
	{
		if (ITEM_1(pos.x, pos.y) && size >= (1 + (9 * (page - 1))))
		{
			advance(itr, 9 * (page - 1));
			DrawTree(*itr);
		}
		else if (ITEM_2(pos.x, pos.y) && size >= (2 + (9 * (page - 1))))
		{
			advance(itr, 1 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if (ITEM_3(pos.x, pos.y) && size >= (3 + (9 * (page - 1))))
		{
			advance(itr, 2 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if (ITEM_4(pos.x, pos.y) && size >= (4 + (9 * (page - 1))))
		{
			advance(itr, 3 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if (ITEM_5(pos.x, pos.y) && size >= (5 + (9 * (page - 1))))
		{
			advance(itr, 4 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if (ITEM_6(pos.x, pos.y) && size >= (6 + (9 * (page - 1))))
		{
			advance(itr, 5 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if (ITEM_7(pos.x, pos.y) && size >= (7 + (9 * (page - 1))))
		{
			advance(itr, 6 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if (ITEM_8(pos.x, pos.y) && size >= (8 + (9 * (page - 1))))
		{
			advance(itr, 7 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if (ITEM_9(pos.x, pos.y) && size >= (9 + (9 * (page - 1))))
		{
			advance(itr, 8 + (9 * (page - 1)));
			DrawTree(*itr);
		}
		else if(B_L_CORNER(pos.x, pos.y, al_get_bitmap_width(right), al_get_bitmap_height(right)) && (size > (9 * page)))
		{
			NextPage(blockchain, ++page);
		}
		else if (B_R_CORNER(pos.x, pos.y, al_get_bitmap_width(right), al_get_bitmap_height(right)) && (page != 1))
		{
			PrevPage(blockchain, page);
		}
	}
	return;
}

void
Allegro::NextPage(list<Block>& blockchain, int page)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	int posx = 30;
	int posy = 30;
	list<Block>::iterator itr = blockchain.begin();

	if (blockchain.size() > (9 * page))
	{
		al_draw_bitmap(right, DISPLAY_W, DISPLAY_H-al_get_bitmap_height(right), ALLEGRO_ALIGN_RIGHT);
	}
	if (page != 1)
	{
		advance(itr, 9 * (page - 1));
		al_draw_bitmap(left, 0, DISPLAY_H, ALLEGRO_ALIGN_LEFT);
	}

	for (; posy <= (DISPLAY_H - IMAGE_H); posy += (IMAGE_H + 30))
	{
		for (; posx <= (DISPLAY_W - IMAGE_W); posx += (IMAGE_W + 30))
		{
			if (itr != blockchain.end())
			{
				DrawBlock(*itr, posx, posy, IMAGE_W, IMAGE_H);
				++itr;
			}
		}
	}

	al_flip_display();

	int ev;
	do
	{
		ev = getNextEvent();
		if (ev == ev_mouse)
		{
			mouse_dispatcher(blockchain, page);
		}

	} while (ev != ev_quit);
	return;
	
}

void
Allegro::PrevPage(list<Block>& blockchain, int page)
{
	NextPage(blockchain, --page);
	return;
}

void
Allegro::DrawTree(Block& bloque)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	int height = findTreeH(bloque.getRoot());
	int cant = bloque.getCantTxs();
	int w = (int)((DISPLAY_W / cant) - DIF);
	int h = (int)(((DISPLAY_H - al_get_bitmap_height(left)) / height) - DIF);

	DrawFloor(cant, w, h, DIF);
	al_flip_display();


	/*
	DISPLAY_W/cant (-1 casteado a int) -->ancho de imagen
	(DISPLAY_H-ARROW_H)/height (-1 casteado a int) -->largo de imagen
				le dejo lugar a la flecha
	-uso al_draw_scaled_bitmap

	-dibujar arbol
	-dibujar texto necesario  (???)
	-dibujar flechita para volver

	-descifrar como dibujar las flechita (???)

	DrawFloor(cant, w, h, DIF, 0)

	DrawFloor(cant, w, h, DIF, 0)
	*/
}

void
Allegro::DrawFloor(int cant, int img_w, int img_h, int block_dis, int border_dis, int floor, int aux)
{
	if (cant == 1)
	{
		al_draw_scaled_bitmap(block_img, 0, 0, al_get_bitmap_width(block_img), al_get_bitmap_height(block_img),
			DISPLAY_W/2, 0, img_w, img_h, ALLEGRO_ALIGN_CENTER);
		return;
	}
	else
	{
		int x = border_dis;
		int y = (DISPLAY_H - al_get_bitmap_height(left) - al_get_bitmap_height(block_img)) - ((al_get_bitmap_height(block_img) + DIF)*floor);

		for (int i = 0; i < cant; i++, (x += (al_get_bitmap_width(block_img) + block_dis)))
		{
			al_draw_scaled_bitmap(block_img, 0, 0, al_get_bitmap_width(block_img), al_get_bitmap_height(block_img),
				x, y, img_w, img_h, 0);
		}

		DrawFloor(cant / 2, img_w, img_h, (block_dis * 2) + DIF, border_dis+DIF*aux, ++floor, aux*2);
		return;
	}


}


int findTreeH(MerkleRoot* root)
{
	int height = 0;
	MerkleNode* node = root->getLeft();
	height++;

	while (!node->isLastBlock())
	{
		node = node->getLeft();
		height++;
	}
	return height;
}
