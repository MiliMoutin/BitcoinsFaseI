#pragma once
#include "Allegro.h"
#include "Miners.h"

class MinerView: public Observer
{
public:
	MinerView(Allegro& alle);
	~MinerView(){}
	void update(void* model);
private:
	ALLEGRO_SAMPLE* sound;
	void ChaChig(Miner* min);
};