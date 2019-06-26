#pragma once
#include "Subject.h"

using namespace std;

class Cajita :public Subject
{
public:
	Cajita() { from = ""; to = ""; amount = ""; }
	void setFrom(string f) { this->from = f; notifyAllObservers(); }
	void setTo(string t) { this->to = t; notifyAllObservers(); }
	void setAmount(string am) { this->amount = am; notifyAllObservers(); }
	string getFrom() { return this->from; }
	string getTo() { return this->to; }
	string getAmount() { return this->amount; }
	void reset() { from = ""; to = ""; amount = ""; notifyAllObservers(); }
private:
	string from;
	string to;
	string amount;
};