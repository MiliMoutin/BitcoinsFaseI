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
	Allegro Simalle;

	Simulation EDACoin(5,5,3);
	if (!EDACoin.creationSuccessful()) {
		cout << "Simulation creation failed" << endl;
	}
	SimulationView vi(Simalle, EDACoin.get_total());
	EDACoin.attach(vi);
	for (int i = 0; i < EDACoin.get_total(); i++)
	{
		EDACoin.get_nodes()[i]->Subject::attach(vi.get_node_views()[i]);
		//BlockchainView BCv(Simalle);
		//EDACoin.get_nodes()[i]->Subject::attach(BCv);
	}
	CajitaView cv = vi.get_caja_view();
	(EDACoin.get_cajita()[0])->attach(cv);
	EDACoin.notifyAllObservers();
	
	SimCtrl ctr(vi.get_display());
	/*
	list<Block> bl = ((Full*)(EDACoin.get_nodes()[0]))->getBchain();


	
	BlockchainView BCv(Simalle);
	BlockchainCtrl BCctr(BCv.get_display());

	for (int i = 0; i < EDACoin.get_total(); i++)
	{
		if (EDACoin.get_nodes()[i]->getType() == "Full")
		{
			EDACoin.get_nodes()[i]->Subject::attach(BCv);
		}
	}
*/
	ALLEGRO_EVENT ev, bc_ev;
	do
	{
		ev = ctr.getEvent();
		ctr.Alle_dispatcher(&EDACoin, ev);
		/*if (ctr.stat == node)
		{
			bc_ev = BCctr.getEvent();
			BCctr.Alle_dispatcher(EDACoin.get_nodes()[0], bc_ev);
		}*/
	}while (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);

	return 0;
}

