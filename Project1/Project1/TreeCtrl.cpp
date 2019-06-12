#include "TreeCtrl.h"

TreeCtrl::TreeCtrl(ALLEGRO_DISPLAY* display)
{
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
}

TreeCtrl::~TreeCtrl()
{
}

void
TreeCtrl::dispatcher(void* model)
{
	Block* b = (Block*)model;
	ALLEGRO_EVENT ev = getEvent();
	switch (ev.type)
	{
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
	{
		return;
	}
	default:
	{
		break;
	}
	}

}