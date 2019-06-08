#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"

#define N_DISPLAY_W 700
#define N_DISPLAY_H 700
#define GRAPH_RADIUS ((N_DISPLAY_W/2)-30)

class Observer {
public:
	Observer() {};
	Observer(const Observer& orig) {};
	virtual void update(void* model) = 0;
	virtual ~Observer() {};
};
