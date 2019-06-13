#include "BlockchainCtrl.h"

BlockchainCtrl::BlockchainCtrl(ALLEGRO_DISPLAY* display)
{
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
}

BlockchainCtrl::~BlockchainCtrl()
{
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
			
			if (ITEM_1(pos.x, pos.y) && size >= (1 + (9 * (page - 1))))
			{
				advance(itr, 9 * (page - 1));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_2(pos.x, pos.y) && size >= (2 + (9 * (page - 1))))
			{
				advance(itr, 1 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_3(pos.x, pos.y) && size >= (3 + (9 * (page - 1))))
			{
				advance(itr, 2 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_4(pos.x, pos.y) && size >= (4 + (9 * (page - 1))))
			{
				advance(itr, 3 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_5(pos.x, pos.y) && size >= (5 + (9 * (page - 1))))
			{
				advance(itr, 4 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_6(pos.x, pos.y) && size >= (6 + (9 * (page - 1))))
			{
				advance(itr, 5 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_7(pos.x, pos.y) && size >= (7 + (9 * (page - 1))))
			{
				advance(itr, 6 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_8(pos.x, pos.y) && size >= (8 + (9 * (page - 1))))
			{
				advance(itr, 7 + (9 * (page - 1)));
				(*itr).notifyAllObservers();
			}
			else if (ITEM_9(pos.x, pos.y) && size >= (9 + (9 * (page - 1))))
			{
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
				PrevPage(nodo, page);
			}
			break;
		}
	}
	}
}