#include <iostream>
#include<list>
#include <string>
#include "Allegro.h"
#include "SPV.h"
#include "Full.h"
/*
int findTreeH(MerkleRoot* root);
list<Block> findBchain(Node* nodo);
*/
using namespace std;

Allegro::Allegro()
{
	if (!al_init()) 
	{ 
		cout<<"failed to initialize allegro!\n";
		init_ok = false;
		return;
	}

	if (!al_install_mouse()) 
	{
		cout<<"failed to initialize the mouse!\n";
		init_ok = false;
		return;
	}
	
	al_init_acodec_addon();

	cash_sound=al_load_sample("ChaChing.mp3");
	if (!cash_sound)
	{
		cout << "failed to load mp3\n";
	}
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font(TEXTFONT, TEXTSIZE, 0);
	if (!font) 
	{
		cout<<"Could not load text font.\n";
		//al_destroy_event_queue(event_queue);
		return;
	}

	al_init_image_addon();

	al_init_primitives_addon();

	right= al_load_bitmap(ARROW_RIGHT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		//al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_bitmap(right);
		al_destroy_sample(cash_sound);
		init_ok = false;
		return;
	}

	left = al_load_bitmap(ARROW_LEFT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		//al_destroy_event_queue(event_queue);
		al_destroy_font(font);
		al_destroy_bitmap(right);
		al_destroy_bitmap(left);
		al_destroy_sample(cash_sound);
		init_ok = false;
		return;
	}
	//al_register_event_source(event_queue, al_get_mouse_event_source()); //REGISTRAMOS EL MOUSE
	init_ok = true;
	page = 1;
	return;
}


Allegro::~Allegro()
{
	//al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_bitmap(right);
	al_destroy_bitmap(left);
	al_destroy_sample(cash_sound);
}
