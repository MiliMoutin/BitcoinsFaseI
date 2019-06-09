#pragma once
#include "Subject.h"

using namespace std;

class Cajita :public Subject
{
public:
	void setFrom(string f) { from = f; }
	void setTo(string t) { to = t; }
	void setAmount(string am) { amount = am; }
	string getFrom() { return from; }
	string getTo() { return to; }
	string getAmount() { return amount; }
	void reset() { from = ""; to = ""; amount = ""; }
private:
	string from;
	string to;
	string amount;
};