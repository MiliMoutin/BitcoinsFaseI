#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs
#include <allegro5/allegro_primitives.h>
#include "Block.h"
#include "Observer.h"
#include "Node.h"

#define DISPLAY_H	700
#define DISPLAY_W	700
#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15
#define BLOCK_IMAGE "bloque.png"
#define ARROW_RIGHT_IMAGE "Right.png"
#define ARROW_LEFT_IMAGE "Left.png"
#define SPACE_BTW 30
#define IMAGE_W ((DISPLAY_W/3)-SPACE_BTW)
#define IMAGE_H ((DISPLAY_H/3)-SPACE_BTW)
#define DIF 10

#define RADIO TEXTSIZE*2
#define NODE_DIF_X ((RADIO*5)+10)
#define NODE_DIF_Y 0

#define FIRST_COL(x) (((x)>=SPACE_BTW) && ((x) <= (SPACE_BTW+IMAGE_W)))
#define SECOND_COL(x) (((x) >= ((SPACE_BTW*2)+IMAGE_W)) && ((x) <= ((SPACE_BTW*2)+(IMAGE_W*2))))
#define THIRD_COL(x) (((x) >= ((SPACE_BTW*3)+(IMAGE_W*2))) && ((x) <= ((SPACE_BTW*3)+(IMAGE_W*3))))

#define FIRST_ROW(x) (((x)>=SPACE_BTW) && ((x) <= (SPACE_BTW+IMAGE_H)))
#define SECOND_ROW(x) (((x) >= ((SPACE_BTW*2)+IMAGE_H)) && ((x) <= ((SPACE_BTW*2)+(IMAGE_H*2))))
#define THIRD_ROW(x) (((x) >= ((SPACE_BTW*3)+(IMAGE_H*2))) && ((x) <= ((SPACE_BTW*3)+(IMAGE_H*3))))

#define B_R_CORNER(x,y,dx,dy) (((x)>=(DISPLAY_W-(dx))) && ((x)<=DISPLAY_W)) && (((y)>=(DISPLAY_H-(dy))) && ((y)<=DISPLAY_H))
#define B_L_CORNER(x,y,dx,dy) (((x)<=(dx)) && ((y)<=(dy)))

#define ITEM_1(x,y) (FIRST_ROW(y) && FIRST_COL(x))
#define ITEM_2(x,y) (FIRST_ROW(y) && SECOND_COL(x))
#define ITEM_3(x,y) (FIRST_ROW(y) && THIRD_COL(x))
#define ITEM_4(x,y) (SECOND_ROW(y) && FIRST_COL(x))
#define ITEM_5(x,y) (SECOND_ROW(y) && SECOND_COL(x))
#define ITEM_6(x,y) (SECOND_ROW(y) && THIRD_COL(x))
#define ITEM_7(x,y) (THIRD_ROW(y) && FIRST_COL(x))
#define ITEM_8(x,y) (THIRD_ROW(y) && SECOND_COL(x))
#define ITEM_9(x,y) (THIRD_ROW(y) && THIRD_COL(x))

enum al_event {
	ev_null, ev_quit,
	ev_mouse, ev_tx
};

enum al_status {
	st_exit, st_nodes, st_bchain, st_tree
};

struct display_pos {
	int x;
	int y;
};

struct node_pos
{
	string id;
	string n;
	int cx;
	int cy;
};

class Allegro: public Observer
{
public:
	//constructores
	Allegro(unsigned int w = DISPLAY_W, unsigned int h = DISPLAY_H);
	~Allegro();


	void update(void* model);

	enum al_event getNextEvent(void);
	void dispatcher(al_event ev, Node* nodo);
	al_status get_state() { return state; }
private:
	bool initAllegro_ok(void);
	void ShowGraph(Node* nodo, int cx = DISPLAY_W / 2, int cy = DISPLAY_H / 2, int auxx=NODE_DIF_X, int auxy=NODE_DIF_Y);
	bool ShowBlockchain(Node* nod);


	//unsigned int GetDisplayW();
	//unsigned int GetDisplayH();
	//display_pos GetMousePos();

	void mouse_dispatcher(Node* nodo, int page = 1);
	void DrawNode(Node* nodo, int cx, int cy);
	void DrawBlock(Block& bloque, int x, int y, int w, int h);
	void DrawTree(Block& bloque);
	void DrawFloor(int cant, int img_w, int img_h, int block_dis, int border_dis=0, int floor=0, int aux = 1);
	void NextPage(Node* nodo, int page=1);
	void PrevPage(Node* nodo, int page = 1);

	//void alleTxs();

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* block_img;
	ALLEGRO_BITMAP* right;
	ALLEGRO_BITMAP* left;
	bool init_ok;
	unsigned int display_h;
	unsigned int display_w;
	display_pos pos;
	list<node_pos> nodes_list;
	al_status state;
};