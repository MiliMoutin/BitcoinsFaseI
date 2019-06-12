#pragma once
#include "Observer.h"
#include "Node.h"
#include "Allegro.h"


#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15

#define RADIO TEXTSIZE*2

class NodeView : public Observer
{
public:
	NodeView(Allegro& alle);
	//NodeView(){}
	~NodeView(){}
	void update(void* model);
	void drawNode(Node* nodo);
	//void set_position(int x, int y) { position.px = x; position.py = y; return; }
	//node_pos get_position() { return position; }
private:
	ALLEGRO_FONT* font;
	bool is_drawn;
};