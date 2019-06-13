#include "Subject.h"

/*
Subject::Subject(const Subject& orig)
{
	list<Observer*>::iterator itr = orig.getObs.begin();
	for (; itr != orig.getObs.end(); ++itr)
	{
		observers.push_back(*itr);
	}
	return;
}
*/

Subject::~Subject()
{
	/*
	list<Observer*>::iterator itr = observers.begin();
	for (; itr != observers.end(); ++itr)
	{
		observers.erase(itr);
	}*/
	while (!observers.empty())
	{
		observers.pop_front();
	}
	return;
}

void
Subject::notifyAllObservers()
{
	list<Observer*>::iterator itr = observers.begin();
	for (; itr != observers.end(); ++itr)
	{
		(*itr)->update(this);
	}
	return;
}