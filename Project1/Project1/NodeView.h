#pragma once

#include "SimulationView.h"
#include "Node.h"

#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15
#define RADIO TEXTSIZE*2

struct node_pos
{
	int px;
	int py;
};

class NodeView : public SimulationView
{
public:
	NodeView() { is_drawn = false; }
	void drawNode(Node& nodo);
	void set_position(int x, int y) { position.px = x; position.py = y; return; }
	node_pos get_position() { return position; }
private:
	node_pos position;
	bool is_drawn;
};