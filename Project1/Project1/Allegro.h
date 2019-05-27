#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

#define DISPLAY_H	1300
#define DISPLAY_W	1300
#define TEXTFONT "allegrofiles\\textfont.ttf"
#define TEXTSIZE 30
#define BLOCK_IMAGE "block.png"
#define ARROW_RIGHT_IMAGE "right.png"
#define ARROW_LEFT_IMAGE 
#define IMAGE_W 300
#define IMAGE_H 300
#define SPACE_BTW 30

#define FIRST_COL(x) (((x)>=SPACE_BTW) && ((x) <= (SPACE_BTW+IMAGE_W)))
#define SECOND_COL(x) (((x) >= ((SPACE_BTW*2)+IMAGE_W)) && ((x) <= ((SPACE_BTW*2)+(IMAGE_W*2))))
#define THIRD_COL(x) (((x) >= ((SPACE_BTW*3)+(IMAGE_W*2))) && ((x) <= ((SPACE_BTW*3)+(IMAGE_W*3))))

#define FIRST_ROW(x) (((x)>=SPACE_BTW) && ((x) <= (SPACE_BTW+IMAGE_H)))
#define SECOND_ROW(x) (((x) >= ((SPACE_BTW*2)+IMAGE_H)) && ((x) <= ((SPACE_BTW*2)+(IMAGE_H*2))))
#define THIRD_ROW(x) (((x) >= ((SPACE_BTW*3)+(IMAGE_H*2))) && ((x) <= ((SPACE_BTW*3)+(IMAGE_H*3))))

#define B_L_CORNER(x,y,dx,dy) (((x)>=(DISPLAY_W-(dx))) && ((x)<=DISPLAY_W)) && (((y)>=(DISPLAY_H-(dy))) && ((y)<=DISPLAY_H))
#define B_R_CORNER(x,y,dx,dy) (((x)<=(dx)) && ((y)<=(dy)))

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
	ev_mouse,
	/*ev_tile1, ev_tile2, ev_tile3, ev_tile4, ev_tile5, ev_tile6, ev_tile7, ev_tile8, ev_tile9,
	ev_right, ev_left, ev_prev*/
};

//enum align { center, right, left };

struct display_pos {
	int x;
	int y;
};

class Allegro
{
public:
	//constructores
	Allegro(unsigned int w = DISPLAY_W, unsigned int h = DISPLAY_H);
	~Allegro();
	bool initAllegro_ok(void);

	
	bool ShowAlle(list<Block>& blockchain);
	//void DrawTree(MerkleRoot& root);

	enum al_event getNextEvent(void);
	//void printText(const char* text, int x, int y, enum align al, ALLEGRO_FONT * al_font = NULL);

	unsigned int GetDisplayW();
	unsigned int GetDisplayH();

	//void drawImage(ALLEGRO_BITMAP* image, int x, int y, int width = 0, int height = 0);
	display_pos GetMousePos();

private:
	void DrawBlock(Block& bloque, int x, int y, int w, int h);
	void mouse_dispatcher(int size, int page=1);
	void NextPage(list<Block>& blockchain, int page=1);

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
};