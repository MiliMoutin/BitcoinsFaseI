#include <iostream>
#include<list>
#include <string>
#include "Allegro.h"
#include "SPV.h"
#include "Full.h"
/*
int findTreeH(MerkleRoot* root);
list<Block> findBchain(Node* nodo);
*/
using namespace std;

Allegro::Allegro()
{
	if (!al_init()) 
	{ 
		cout<<"failed to initialize allegro!\n";
		init_ok = false;
		return;
	}

	if (!al_install_mouse()) 
	{
		cout<<"failed to initialize the mouse!\n";
		init_ok = false;
		return;
	}
	/*
	event_queue = al_create_event_queue();
	if (!event_queue) 
	{
		cout<<"failed to create event_queue!\n";
		init_ok = false;
		return;
	}
	*/
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font(TEXTFONT, TEXTSIZE, 0);
	if (!font) 
	{
		cout<<"Could not load text font.\n";
		//al_destroy_event_queue(event_queue);
		return;
	}

	al_init_image_addon();

	al_init_primitives_addon();

	right= al_load_bitmap(ARROW_RIGHT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		//al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_bitmap(right);
		init_ok = false;
		return;
	}

	left = al_load_bitmap(ARROW_LEFT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		//al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_bitmap(right);
		al_destroy_bitmap(left);
		init_ok = false;
		return;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_flip_display();
	//al_register_event_source(event_queue, al_get_mouse_event_source()); //REGISTRAMOS EL MOUSE
	init_ok = true;
	return;
}


Allegro::~Allegro()
{
	//al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_bitmap(right);
	al_destroy_bitmap(left);
}


/*
void
Allegro::update(void* model)
{
	Node* nodo = (Node*)model;
	ShowGraph(nodo);
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
		state = st_exit;
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
	case ALLEGRO_EVENT_KEY_UP:
	{
		if (ev.keyboard.keycode == ALLEGRO_KEY_T)
		{
			return ev_tx;
		}
		else
		{
			return ev_null;
		}
	}
	default:
	{
		return ev_null;
		break;
	}
	}
}


void
Allegro::dispatcher(al_event ev, Node* nodo)		//este iria asi como esta al controller. Pasarle tambien un Allegro?
{
	switch (ev)
	{
	case ev_mouse:
	{
		mouse_dispatcher(nodo);
		break;
	}
	case ev_tx:
	{
		//alleTxs();
		break;
	}
	case ev_null:
	{
		break;
	}
	}
	return;
}


bool
Allegro::initAllegro_ok()
{
	return init_ok;
}


void
Allegro::ShowGraph(Node* nodo, int cx, int cy, int auxx, int auxy)
{
	//int auxx = (RADIO * 5) + 10, auxy = 0;		//esto tienen que ser defines y despues hago parametros =esto
	node_pos pos;
	string type = nodo->getType();
	pos.id = nodo->getID();
	pos.cx = cx;
	pos.cy = cy;
	
	for (node_pos p : nodes_list)
	{
		if (pos.id == p.id)			//si ya dibuje el nodo, no lo vuelvo a dibujar
		{
			return;
		}
	}
	nodes_list.push_back(pos);
	
	int size = nodo->getNeighbours().size();
	for (Node* n : nodo->getNeighbours())
	{
		
		if (size > 1)
		{
			al_draw_line(cx, cy, cx - auxx, cy - auxy, al_map_rgb(0, 0, 0), 0);
		}
		al_flip_display();
		ShowGraph(n, cx - auxx, cy - auxy, auxx, auxy);
		auxx -= ((RADIO*2)+10);
		auxy += ((RADIO*2) + 10);
	}
	DrawNode(nodo, cx, cy);

	return;
}


bool
Allegro::ShowBlockchain(Node* nod)
{
	list<Block> blockchain = findBchain(nod);

	if (blockchain.size() == 0)
	{
		cout << "Blockchain empty." << endl;
		al_draw_text(font, al_map_rgb(255, 0, 0), DISPLAY_W / 2, DISPLAY_H / 2, ALLEGRO_ALIGN_CENTER, "Blockchain empty.");
		al_flip_display();
		return false;
	}

	NextPage(nod);
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
	*//*
	return true;
}


void
Allegro::mouse_dispatcher(Node* nodo, int page)
{
	list<Block> blockchain = findBchain(nodo);
	if (state == st_bchain)
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
			else if (B_R_CORNER(pos.x, pos.y, al_get_bitmap_width(right), al_get_bitmap_height(right)) && (size > (9 * page)))
			{
				NextPage(nodo, ++page);
			}
			else if (B_L_CORNER(pos.x, pos.y, al_get_bitmap_width(right), al_get_bitmap_height(right)) && (page != 1))
			{
				PrevPage(nodo, page);
			}
			else
			{
				int x = pos.x - (DISPLAY_W/2);
				int y = pos.y - (DISPLAY_H-RADIO);
				float d = sqrt(pow(x, 2) + pow(y, 2));
				if (d <= RADIO)
				{
					state = st_nodes;
					nodes_list.erase(nodes_list.begin(), nodes_list.end());
					al_clear_to_color(al_map_rgb(255, 255, 255));
					ShowGraph(nodo);
				}
			}
		}
	}
	else if (state == st_nodes)
	{
		for (node_pos p : nodes_list)
		{
			int x = pos.x - p.cx;
			int y = pos.y - p.cy;
			float d = sqrt(pow(x, 2) + pow(y, 2));
			if (d <= RADIO)
			{
				state = st_bchain;
				al_clear_to_color(al_map_rgb(255, 255, 255));
				ShowBlockchain(nodo);
			}
		}
	}
	else if (state == st_tree)
	{
		if (B_R_CORNER(pos.x, pos.y, al_get_bitmap_width(right), al_get_bitmap_height(right)) && (page != 1))
		{
			state = st_bchain;
			al_clear_to_color(al_map_rgb(255, 255, 255));
			ShowBlockchain(nodo);
		}
		else
		{
			int x = pos.x - (DISPLAY_W / 2);
			int y = pos.y - (DISPLAY_H - RADIO);
			float d = sqrt(pow(x, 2) + pow(y, 2));
			if (d <= RADIO)
			{
				state = st_nodes;
				nodes_list.erase(nodes_list.begin(), nodes_list.end());
				al_clear_to_color(al_map_rgb(255, 255, 255));
				ShowGraph(nodo);
			}
		}
	}
	return;
}


void
Allegro::DrawNode(Node* nodo, int cx, int cy)
{
	
	al_draw_filled_circle(cx, cy, RADIO, al_map_rgb(0, 255, 0));
	al_draw_text(font, al_map_rgb(255, 0, 0), cx, cy-TEXTSIZE, ALLEGRO_ALIGN_CENTER, nodo->getType().c_str());
	al_flip_display();
	return;
}


/*
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
*/
/*

void
Allegro::DrawBlock(Block& bloque, int x, int y, int w, int h)
{
	al_draw_scaled_bitmap(block_img, 0, 0, al_get_bitmap_width(block_img), al_get_bitmap_height(block_img), x, y, w, h, 0);

	string id = to_string(bloque.getId());
	string cantx = to_string(bloque.getCantTxs());
	string aux1("ID: " + id);
	string aux2("Txs: " + cantx);
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y + 10, 0, aux1.c_str());
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y + TEXTSIZE, 0, aux2.c_str());
	return;
}


void
Allegro::DrawTree(Block& bloque)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	int height = findTreeH(bloque.getRoot());
	
	int cant = bloque.getCantTxs();
	_Is_pow_2(cant);
	int w = (int)((DISPLAY_W / cant) - DIF);
	int h = (int)(((DISPLAY_H - al_get_bitmap_height(left)) / height) - DIF);

	al_draw_filled_circle(DISPLAY_W / 2, DISPLAY_H - RADIO, RADIO, al_map_rgb(0, 255, 0));
	al_draw_text(font, al_map_rgb(255, 0, 0), DISPLAY_W / 2, DISPLAY_H - RADIO - TEXTSIZE, ALLEGRO_ALIGN_CENTER, "NODOS");

	DrawFloor(cant, w, h, DIF);

	al_draw_bitmap(left, 0, DISPLAY_H - al_get_bitmap_height(left), ALLEGRO_ALIGN_RIGHT);
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
	*//*
}


void
Allegro::DrawFloor(int cant, int img_w, int img_h, int block_dis, int border_dis, int floor, int aux)
{
	if (cant == 1)
	{
		al_draw_scaled_bitmap(block_img, 0, 0, al_get_bitmap_width(block_img), al_get_bitmap_height(block_img),
			(DISPLAY_W / 2) - img_w, 0, img_w, img_h, ALLEGRO_ALIGN_RIGHT);
		return;
	}
	else
	{
		int x = border_dis;
		int y = (DISPLAY_H - al_get_bitmap_height(left) - img_h - (img_h + DIF)*floor);

		for (int i = 0; i < cant; i++, x += (img_w + block_dis))
		{
			al_draw_scaled_bitmap(block_img, 0, 0, al_get_bitmap_width(block_img), al_get_bitmap_height(block_img),
				x, y, img_w, img_h, ALLEGRO_ALIGN_RIGHT);
			al_flip_display();
		}

		DrawFloor(cant / 2, img_w, img_h, (block_dis * 2) + DIF, border_dis + DIF * aux, ++floor, aux * 2);
		return;
	}


}


void
Allegro::NextPage(Node* nodo, int page)
{
	list<Block> blockchain = findBchain(nodo);
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

	al_draw_filled_circle(DISPLAY_W / 2, DISPLAY_H - RADIO, RADIO, al_map_rgb(0, 255, 0));
	al_draw_text(font, al_map_rgb(255, 0, 0), DISPLAY_W / 2, DISPLAY_H - RADIO - TEXTSIZE, ALLEGRO_ALIGN_CENTER, "NODOS");

	al_flip_display();

	int ev;
	do
	{
		ev = getNextEvent();
		if (ev == ev_mouse)
		{
			mouse_dispatcher(nodo, page);
		}

	} while (ev!=ev_quit);

	return;
	
}

void
Allegro::PrevPage(Node* nodo, int page)
{
	NextPage(nodo, --page);
	return;
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

list<Block> findBchain(Node* nodo)
{
	string type = nodo->getType();
	if (type == "Full")
	{
		Full* n = (Full*)nodo;
		return n->getBchain();
	}
	else
	{
		return findBchain(nodo->getNeighbours().front());
	}
}*/