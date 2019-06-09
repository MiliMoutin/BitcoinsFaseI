#pragma once
#include "SimulationView.h"

class CajitaView : public Observer
{
public:
	void update(void*model);
//private:
	void drawCajita(Cajita* caja);
};
