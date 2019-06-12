#include "SimCtrl.h"

SimCtrl::SimCtrl(ALLEGRO_DISPLAY* display)
{
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
}

SimCtrl::~SimCtrl()
{
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