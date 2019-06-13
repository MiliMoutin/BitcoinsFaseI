#include "Output.h"


Output::Output() {

}

Output::Output(string idReceiver, unsigned long amount) {
	this->idReceiver = idReceiver; 
	this->amount = amount;
}

nlohmann::json Output::transformToJson(){	
	nlohmann::json j; 
	j["PublicKey"] = idReceiver; 
	j["EDACoins"] = to_string(amount); 
	return j; 
}
