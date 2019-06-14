#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>


using namespace std;

/*public key amount*/

class Output {
public:
	Output();
	Output(nlohmann::json j);
	Output(string idReceiver, unsigned long amount);
	string getIdReceiver() { return idReceiver; }
	double getAmount() { return amount; }
	nlohmann::json transformToJson(); 
private:
	string idReceiver;
	double amount;
};
