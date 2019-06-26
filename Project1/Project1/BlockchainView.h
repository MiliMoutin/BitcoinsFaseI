#pragma once
#include "Observer.h"
#include "Block.h"
#include <list>
#include "Allegro.h"
/*
#define DISPLAY_H	700
#define DISPLAY_W	700
#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15
#define ARROW_RIGHT_IMAGE "Right.png"
#define ARROW_LEFT_IMAGE "Left.png"
#define ARROW_H 25
#define ARROW_W 50
#define SPACE_BTW 30
#define IMAGE_W ((DISPLAY_W/3)-SPACE_BTW)
#define IMAGE_H ((DISPLAY_H/3)-SPACE_BTW)
*/
class BlockchainView : public Observer
{
public:
	BlockchainView(Allegro& alle);
	~BlockchainView();
	void update(void* model);
	ALLEGRO_DISPLAY* get_display() { return display; }
	//bool is_it_drawn() { return is_drawn; }
	//void set_draw(bool d) { is_drawn = d; }
private:
	void drawBChain(list<Block> b_chain);
	void DrawPage(list<Block> blockchain);
	//void PrevPage(list<Block> blockchain, int page);
	void DrawBlock(Block& bloque, int x, int y, int w, int h);
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* right;
	ALLEGRO_BITMAP* left;
	int page;

	//bool is_drawn;
	//list<BlockView*> b_chain;
};

