#pragma once
#include "Observer.h"
#include "Block.h"
#include <list>

#define DISPLAY_H	700
#define DISPLAY_W	700
#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15
#define ARROW_RIGHT_IMAGE "Right.png"
#define ARROW_LEFT_IMAGE "Left.png"
#define SPACE_BTW 30
#define IMAGE_W ((DISPLAY_W/3)-SPACE_BTW)
#define IMAGE_H ((DISPLAY_H/3)-SPACE_BTW)

class BlockchainView : public Observer
{
public:
	BlockchainView();
	~BlockchainView();
	void update(void* model);
private:
	void drawBChain(list<Block> b_chain);
	void NextPage(list<Block> blockchain, int page = 1);
	void PrevPage(list<Block> blockchain, int page);
	void DrawBlock(Block& bloque, int x, int y, int w, int h);
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* right;
	ALLEGRO_BITMAP* left;
	//list<BlockView*> b_chain;
};

