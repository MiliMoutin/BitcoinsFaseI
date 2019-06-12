#include "AllegroCtrl.h"
#include <iostream>

using namespace std;

AllegroCtrl::AllegroCtrl()
{
	if (!al_install_mouse())
	{//initialize mouse.
		cout << "failed to initialize the mouse!\n";
		return;
	}

	event_queue = al_create_event_queue();//create event queue.
	if (!event_queue)
	{
		cout << "failed to create event_queue!\n";
		return;
	}

	if (!al_install_keyboard())
	{
		cout << "failed to initialize the keyboard\n";
		return;
	}
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source()); //REGISTRAMOS EL MOUSE
}

AllegroCtrl::~AllegroCtrl()
{
	al_destroy_event_queue(event_queue);
}


ALLEGRO_EVENT
AllegroCtrl::getEvent()
{
	ALLEGRO_EVENT ev;
	al_get_next_event(event_queue, &ev);
	return ev;
}