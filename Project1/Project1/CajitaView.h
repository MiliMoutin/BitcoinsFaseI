#pragma once
#include "Observer.h"

class CajitaView : public Observer
{
public:
	void update(void*model);
private:
	void drawCajita();
};
