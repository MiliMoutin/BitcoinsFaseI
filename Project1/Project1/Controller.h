#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "Defines.h"

struct display_pos {
	int x;
	int y;
};

class Controller
{
public:
	Controller(){}
	virtual ~Controller(){}
	virtual void dispatcher(void* model) = 0;
	virtual ALLEGRO_EVENT getEvent() = 0;
};

/*

ALLEGRO_EVENT* ev;
while(cont.is_not_quit(ev)
{
	dispatcher(ev)
}
*/