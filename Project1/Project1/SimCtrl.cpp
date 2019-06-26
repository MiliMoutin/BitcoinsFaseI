#include "SimCtrl.h"
#include "BlockchainView.h"
#include "BlockchainCtrl.h"

SimCtrl::SimCtrl(ALLEGRO_DISPLAY* display)
{
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
}


void
SimCtrl::Alle_dispatcher(void* model, ALLEGRO_EVENT ev)
{
	Simulation* sim = (Simulation*)model;
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
			int x = pos.x - sim->get_nodes()[i]->get_position().px;
			int y = pos.y - sim->get_nodes()[i]->get_position().py;
			float d = sqrt(pow(x, 2) + pow(y, 2));
			if (d <= RADIO)
			{
				if (sim->get_nodes()[i]->getType() != "SPV")		//Si hice click en algun nodo que no sea SPV...  //y si clickeo un SPV?
				{
					stat = node;
					sim->set_next_pn(i);
					sim->get_nodes()[i]->notifyAllObservers();		//... llama a los observers del nodo
				}
			}
			else
			{
				sim->set_next_pn(-1);
			}
		}
		//stat = no_state;		//no estoy clickeando en la cajita
		if ((pos.y >= ((C_DISPLAY_H / 2) + N_DISPLAY_H)) && (pos.y <= ((C_DISPLAY_H / 2) + N_DISPLAY_H + TEXTSIZE)))		//y>=650  
		{
			if (FROM(pos.x))
			{
				stat = from;		//hice click en from
			}
			else if (TO(pos.x))
			{
				stat = to;			//hice click en to
			}
			else if (AMOUNT(pos.x))
			{
				stat = amount;		//hice click en amount
			}
		}
		else if (SEND(pos.x, pos.y))		//hice click en send
		{
			sim->createTx(sim->get_cajita()[0]->getFrom(), sim->get_cajita()[0]->getTo(), stod(sim->get_cajita()[0]->getAmount()));
			sim->get_cajita()[0]->reset();
			stat = no_state;
		}
		else if (stat != node)
		{
			stat = no_state;
		}
		break;
	}
	case ALLEGRO_EVENT_KEY_CHAR:
	{//escribo en la cajita
		switch (stat)
		{
		case from:
		{
			string aux(sim->get_cajita()[0]->getFrom());		//creo string auxiliar con el from de la cajita
			if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)		//si aprete el backspace
			{
				if (!aux.empty())
				{
					aux.pop_back();		//elimino una letra
				}
			}
			else if (ev.keyboard.keycode <= ALLEGRO_KEY_9)		//si apreto una tecla (entre A-Z y 0-9)
			{
				aux.push_back(ev.keyboard.unichar);		//la meto en el string
			}
			sim->get_cajita()[0]->setFrom(aux);		//seteo la cajita con el string auxiliar
			break;
		}
		case to:
		{													//idem
			string aux = sim->get_cajita()[0]->getTo();
			if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
			{
				if (!aux.empty())
				{
					aux.pop_back();		
				}
			}
			else if (ev.keyboard.keycode <= ALLEGRO_KEY_9)
			{
				aux.push_back(ev.keyboard.unichar);
			}
			sim->get_cajita()[0]->setTo(aux);
			break;
		}
		case amount:
		{													//idem
			string aux = sim->get_cajita()[0]->getAmount();
			if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
			{
				if (!aux.empty())
				{
					aux.pop_back();		
				}
			}
			else if ((ev.keyboard.keycode >= ALLEGRO_KEY_0)&&(ev.keyboard.keycode <= ALLEGRO_KEY_9))		//solo acepto numeros
			{
				aux.push_back(ev.keyboard.unichar);
			}
			sim->get_cajita()[0]->setAmount(aux);
			break;
		}
		case no_state: case node:
		{
			//sim->keepMining();
			break;
		}
		}
	}
	}
}
