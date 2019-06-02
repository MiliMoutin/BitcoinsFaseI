#pragma once

#include <iostream>
#include <list>
#include "Observer.h"

using namespace std;

class Subject {
public:
	Subject() {};
	Subject(const Subject& orig);
	virtual ~Subject();
	void attach(Observer& o) { observers.push_back(o); }
	void deAttach(Observer& o);		//NI IDEA MONO
	list<Observer&> getObs() { return observers; }
protected:
	void notifyAllObservers();
private:
	list<Observer&> observers;
};