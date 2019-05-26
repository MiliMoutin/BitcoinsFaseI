#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

#define DISPLAY_H	1700
#define DISPLAY_W	1300
#define TEXTFONT "allegrofiles\\textfont.ttf"
#define TEXTSIZE 30
#define BLOCK_IMAGE "block.png"
#define ARROW_RIGHT_IMAGE "r_arrow.png"
#define IMAGE_W 300
#define IMAGE_H 300

enum al_event {
	ev_null, ev_quit,
	ev_tile1, ev_tile2, ev_tile3, ev_tile4, ev_tile5, ev_tile6, ev_tile7, ev_tile8, ev_tile9,
	ev_right, ev_left, ev_prev,
	ev_mouse
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

	void DrawBlock(Block& bloque, int x, int y, int w, int h);

	//void DrawTree(MerkleRoot& root);

	enum al_event getNextEvent(void);
	//void printText(const char* text, int x, int y, enum align al, ALLEGRO_FONT * al_font = NULL);

	unsigned int GetDisplayW();
	unsigned int GetDisplayH();

	//void drawImage(ALLEGRO_BITMAP* image, int x, int y, int width = 0, int height = 0);
	display_pos GetMousePos();

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* block_img;
	bool init_ok;
	unsigned int display_h;
	unsigned int display_w;
	display_pos pos;
};