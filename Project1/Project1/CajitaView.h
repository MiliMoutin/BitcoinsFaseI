#pragma once
#include "Observer.h"
#include "Cajita.h"
#include "Allegro.h"


class CajitaView : public Observer
{
public:
	CajitaView(Allegro& alle);
	~CajitaView(){}
	void update(void*model);

	void drawCajita(Cajita* caja);
private:
	ALLEGRO_FONT* font;
};
