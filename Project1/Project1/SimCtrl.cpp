#include "SimCtrl.h"

SimCtrl::SimCtrl(ALLEGRO_DISPLAY* display)
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

	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
	al_register_event_source(event_queue, al_get_mouse_event_source()); //REGISTRAMOS EL MOUSE
}

SimCtrl::~SimCtrl()
{
	al_destroy_event_queue(event_queue);
}

ALLEGRO_EVENT
SimCtrl::getEvent()
{
	ALLEGRO_EVENT ev;
	al_get_next_event(event_queue, &ev);
	return ev;
}

void
SimCtrl::dispatcher(void* model)
{
	Simulation* sim = (Simulation*)model;
	ALLEGRO_EVENT ev = getEvent();
	switch (ev.type)
	{
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
	{
		return;
	}
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	{
		pos.x = ev.mouse.x;
		pos.y = ev.mouse.y;

		for (int i=0;i<sim->get_total();i++)
		{
			
			int x = pos.x - sim->get_nodes()[i].get_position().px;
			int y = pos.y - sim->get_nodes()[i].get_position().py;
			float d = sqrt(pow(x, 2) + pow(y, 2));
			if (d <= RADIO)
			{
				if (sim->get_nodes()[i].getType() != "SPV")
				{
					sim->get_nodes()[i].notifyAllObservers();
				}
			}
		}


		break;
	}
	}
}