#include "CajitaCrl.h"

CajitaCtrl::CajitaCtrl()
{
}

CajitaCtrl::~CajitaCtrl()
{
}


void
CajitaCtrl::dispatcher(void* model)
{
	Cajita* c = (Cajita*)model;
	ALLEGRO_EVENT ev = getEvent();
	switch (ev.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	{
		pos.x = ev.mouse.x;
		pos.y = ev.mouse.y;

		/*
		if(FROM

		if(TO

		if(AMOUNT

		if(SEND
		*/
	}
	}
}
