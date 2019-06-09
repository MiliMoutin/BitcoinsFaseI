#include "CajitaView.h"
#include "Cajita.h"


void
CajitaView::update(void* model)
{
	Cajita* caja = (Cajita*)model;
	drawCajita(caja);
	return;
}


void
CajitaView::drawCajita(Cajita* caja)
{

}