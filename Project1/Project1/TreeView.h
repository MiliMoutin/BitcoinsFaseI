#pragma once
#include "Observer.h"
#include "Block.h"

#define DISPLAY_H	700
#define DISPLAY_W	700

#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15

#define SPACE_BTW 30
#define IMAGE_W ((DISPLAY_W/3)-SPACE_BTW)
#define IMAGE_H ((DISPLAY_H/3)-SPACE_BTW)


#define DIF 10

class TreeView :public Observer
{
public:
	TreeView();
	~TreeView();
	void update(void* model);
	void DrawTree(Block* bloque);
	void DrawFloor(int cant, int img_w, int img_h, int block_dis, int border_dis = 0, int floor = 0, int aux = 1);
	ALLEGRO_DISPLAY* get_display() { return display; }
private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
};