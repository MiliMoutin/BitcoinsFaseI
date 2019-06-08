#pragma once
#include "Subject.h"

using namespace std;

class Cajita :public Subject
{
public:
	void setFrom();
	void setTo();
	void setAmount();
	void reset();
private:
	string from;
	string to;
	string amount;
};