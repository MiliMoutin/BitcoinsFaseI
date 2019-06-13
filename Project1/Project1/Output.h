#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>


using namespace std;

/*public key amount*/

class Output {
public:
	Output();
	Output(string idReceiver, unsigned long amount);
	string getIdReceiver() { return idReceiver; }
	unsigned long getAmount() { return amount; }
	nlohmann::json transformToJson(); 
private:
	string idReceiver;
	unsigned long amount;
};
