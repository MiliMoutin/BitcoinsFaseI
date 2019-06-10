#pragma once
#include "Observer.h"
#include "SimulationView.h"



class CajitaView : public SimulationView //mas que nada eshija de SimView para heredar el font. no me va el font en el observer
{
public:
	void update(void*model);
//private:
	void drawCajita(Cajita* caja);
};
