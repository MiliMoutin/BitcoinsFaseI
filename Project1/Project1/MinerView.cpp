#include "MinerView.h"

MinerView::MinerView(Allegro& alle)
{
	sound = alle.cash_sound;
}

void
MinerView::update(void* model)
{
	Miner* miner = (Miner*)model;
	ChaChig(miner);
	return;
}

void
MinerView::ChaChig(Miner* min)
{
	//Quizas ni tiene que recibir un Miner, depende como sea la funcion de minar
	al_play_sample(sound, 1, ALLEGRO_AUDIO_PAN_NONE, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	return;
}