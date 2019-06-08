#pragma once
#include "Observer.h"
struct node_pos
{
	int px;
	int py;
};
class NodeView : public Observer
{
public:
	void drawNode();
	void drawConnections();
private:
	node_pos position;
	bool is_drawn;
};