#pragma once
#include "Observer.h"
#include "Cajita.h"

#define N_DISPLAY_W 700
#define N_DISPLAY_H 700

#define C_DISPLAY_W N_DISPLAY_W
#define C_DISPLAY_H 200

#define DISPLAY_W N_DISPLAY_W
#define DISPLAY_H (N_DISPLAY_H + C_DISPLAY_H)


#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15

class CajitaView : public Observer
{
public:
	CajitaView();
	~CajitaView();
	void update(void*model);

	void drawCajita(Cajita* caja);
private:
	ALLEGRO_FONT* font;
};
