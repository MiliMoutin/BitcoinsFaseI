#include "TreeCtrl.h"

TreeCtrl::TreeCtrl(ALLEGRO_DISPLAY* display)
{

	event_queue = al_create_event_queue();//create event queue.
	if (!event_queue)
	{
		cout << "failed to create event_queue!\n";
		return;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
}

TreeCtrl::~TreeCtrl()
{
	al_destroy_event_queue(event_queue);
}


ALLEGRO_EVENT
TreeCtrl::getEvent()
{
	ALLEGRO_EVENT ev;
	al_get_next_event(event_queue, &ev);
	return ev;
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