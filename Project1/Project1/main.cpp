#include <iostream>
#include <nlohmann/json.hpp>
#include "Block.h"
#include "MerkleNode.h"
#include "Full.h"
#include "BlockchainCtrl.h"
#include "BlockchainView.h"
#include "Allegro.h"
#include "Simulation.h"
#include "SimulationView.h"
#include "SimCtrl.h"
#include <string>
#include <exception>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


using namespace std;


int main(void) {
	Simulation EDACoin(2, 5, 2);
	if (EDACoin.creationSuccessful()) {
		EDACoin.keepMining();
	}
}

/*
int main(void) {
	Allegro alle;
	Simulation EDACoin(5,5,3);
	if (!EDACoin.creationSuccessful()) {
		cout << "Simulation creation failed" << endl;
	}
	SimulationView vi(Simalle, EDACoin.get_total()); //se crea display principal (mas nodeviewy cajitaview)
	EDACoin.attach(vi);

	for (int i = 0; i < EDACoin.get_total(); i++)
	{
		EDACoin.get_nodes()[i]->Subject::attach(vi.get_node_views()[i]); //
		//BlockchainView BCv(Simalle);
		//EDACoin.get_nodes()[i]->Subject::attach(BCv);
	}
	CajitaView cv = vi.get_caja_view();			//revisar
	(EDACoin.get_cajita()[0])->attach(cv);		// attach(vi.get_caja_view())
	EDACoin.notifyAllObservers();
	
	SimCtrl ctr(vi.get_display());					// controller sim			
	
	//list<Block> bl = ((Full*)(EDACoin.get_nodes()[0]))->getBchain();	


	BlockchainView BCv(Simalle);					//segundo display, muestra la blockchain
	BlockchainCtrl BCctr(BCv.get_display());		// controller de lo que pasa adentro del display de la blockchain	
	EDACoin.getSatochi()->Subject::attach(BCv);
	//EDACoin.getSatochi()->notifyAllObservers();
	/*
	for (int i = 0; i < EDACoin.get_total(); i++)
	{
		if (EDACoin.get_nodes()[i]->getType() == "Full")
		{
			EDACoin.get_nodes()[i]->Subject::attach(BCv);
		}
	}*/
	
	ALLEGRO_EVENT ev, bc_ev;
	do
	{
		al_set_target_backbuffer(vi.get_display());
		ev = ctr.getEvent();
		ctr.Alle_dispatcher(&EDACoin, ev);
		/*if (EDACoin.get_next_pn() != -1)
		{
			int next = EDACoin.get_next_pn();
			int prev = EDACoin.get_prev_pn();
			if (EDACoin.get_prev_pn() != -1)
			{
				EDACoin.get_nodes()[prev]->deAttach();
			}
			
			EDACoin.get_nodes()[next]->Subject::attach(BCv);
			EDACoin.get_nodes()[next]->notifyAllObservers();
		}*/
		//al_set_target_backbuffer(BCv.get_display());
		//bc_ev = BCctr.getEvent();
		//BCctr.Alle_dispatcher(EDACoin.getSatochi(), bc_ev);
		
	}while (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);

	return 0;
}*/


