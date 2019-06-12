#pragma once
#include "Observer.h"
#include "Block.h"
#include "Allegro.h"

class TreeView :public Observer
{
public:
	TreeView(Allegro& alle);
	~TreeView();
	void update(void* model);
	void DrawTree(Block* bloque);
	void DrawFloor(int cant, int img_w, int img_h, int block_dis, int border_dis = 0, int floor = 0, int aux = 1);
	ALLEGRO_DISPLAY* get_display() { return display; }
private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
};