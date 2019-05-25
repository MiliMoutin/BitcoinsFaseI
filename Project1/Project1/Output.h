#pragma once
#include <iostream>
#include <string>


using namespace std;


class Output {
public:
	Output(unsigned long idReceiver, unsigned long amount);
	string getIdReceiver() { return idReceiver; }
	unsigned long getAmount() { return amount; }
private:
	string idReceiver;
	unsigned long amount;
};
