#include "Output.h"
#include <iostream>


using namespace std;


Output::Output() {

}

Output::Output(nlohmann::json j) {
	string i = j["PublicKey"];
	this->idReceiver = i;
	i = j["EDACoins"];
	this->amount =std::stod(i, NULL);
}

Output::Output(string idReceiver, unsigned long amount) {
	this->idReceiver = idReceiver; 
	this->amount = amount;
}

string Output::toSign() {
	return to_string(this->amount) + this->idReceiver;
}

nlohmann::json Output::transformToJson(){	
	nlohmann::json j; 
	j["PublicKey"] = idReceiver; 
	j["EDACoins"] = to_string(amount); 
	return j; 
}


