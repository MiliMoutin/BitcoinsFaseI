#include <iostream>
#include <nlohmann/json.hpp>
#include "Block.h"
#include "MerkleNode.h"
#include "Full.h"
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
	Allegro alle;
	Simulation EDACoin(5,5,3);
	if (!EDACoin.creationSuccessful()) {
		cout << "Simulation creation failed" << endl;
	}
	SimulationView vi(alle, EDACoin.get_total());
	EDACoin.attach(vi);
	EDACoin.notifyAllObservers();
	
	SimCtrl ctr(vi.get_display());
	ALLEGRO_EVENT ev;
	do
	{
		ev = ctr.getEvent();
		ctr.Alle_dispatcher(&EDACoin, ev);
	}while (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);

	return 0;
}

