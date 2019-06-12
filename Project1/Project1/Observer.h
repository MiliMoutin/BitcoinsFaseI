#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "Defines.h"

class Observer {
public:
	Observer() {};
	Observer(const Observer& orig) {};
	virtual void update(void* model) = 0;
	virtual ~Observer() {};
};
