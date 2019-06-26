#pragma once
#include "Subject.h"

using namespace std;

class Cajita :public Subject
{
public:
	Cajita() {}
	void setFrom(string f) { from = f; notifyAllObservers(); }
	void setTo(string t) { to = t; notifyAllObservers(); }
	void setAmount(string am) { amount = am; notifyAllObservers(); }
	string getFrom() { return from; }
	string getTo() { return to; }
	string getAmount() { return amount; }
	void reset() { from = ""; to = ""; amount = ""; notifyAllObservers(); }
private:
	string from;
	string to;
	string amount;
};