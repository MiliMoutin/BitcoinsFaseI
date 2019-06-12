#include "BlockchainCtrl.h"

BlockchainCtrl::BlockchainCtrl(ALLEGRO_DISPLAY* display)
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

BlockchainCtrl::~BlockchainCtrl()
{
	al_destroy_event_queue(event_queue);
}

ALLEGRO_EVENT
BlockchainCtrl::getEvent()
{
	ALLEGRO_EVENT ev;
	al_get_next_event(event_queue, &ev);
	return ev;

}

void
BlockchainCtrl::dispatcher(void* model)
{
	Full* f = (Full*)model;
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

		int size = (f->getBchain().size() - (9 * (page - 1)));
		list<Block>::iterator itr = f->getBchain().begin();
		if (pos.x <= DISPLAY_W && pos.y <= DISPLAY_H)
		{
			int aux;
			if (ITEM_1(pos.x, pos.y) && size >= (1 + (9 * (page - 1))))
			{
				aux = 0;
				advance(itr, 9 * (page - 1));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_2(pos.x, pos.y) && size >= (2 + (9 * (page - 1))))
			{
				aux = 1;
				advance(itr, 1 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_3(pos.x, pos.y) && size >= (3 + (9 * (page - 1))))
			{
				aux = 2;
				advance(itr, 2 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_4(pos.x, pos.y) && size >= (4 + (9 * (page - 1))))
			{
				aux = 3;
				advance(itr, 3 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_5(pos.x, pos.y) && size >= (5 + (9 * (page - 1))))
			{
				aux = 4;
				advance(itr, 4 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_6(pos.x, pos.y) && size >= (6 + (9 * (page - 1))))
			{
				aux = 5;
				advance(itr, 5 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_7(pos.x, pos.y) && size >= (7 + (9 * (page - 1))))
			{
				aux = 7;
				advance(itr, 6 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_8(pos.x, pos.y) && size >= (8 + (9 * (page - 1))))
			{
				aux = 8;
				advance(itr, 7 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_9(pos.x, pos.y) && size >= (9 + (9 * (page - 1))))
			{
				aux = 9;
				advance(itr, 8 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (B_R_CORNER(pos.x, pos.y, ARROW_W, ARROW_H) && (size > (9 * page)))
			{
				page++;
				f->notifyAllObservers();
			}
			else if (B_L_CORNER(pos.x, pos.y, ARROW_W, ARROW_H) && (page != 1))
			{
				page--;
				//PrevPage(nodo, page);
			}
			break;
		}
	}
	}
}