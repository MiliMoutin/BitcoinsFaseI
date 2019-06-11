#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>


using namespace std;


class Output {
public:
	Output();
	Output(string idReceiver, unsigned long amount);
	string getIdReceiver() { return idReceiver; }
	unsigned long getAmount() { return amount; }
	nlohmann::json transformToJson() { nlohmann::json j; j["PublicKey"] = idReceiver; j["EDACoins"] = to_string(amount); }

private:
	string idReceiver;
	unsigned long amount;
};
