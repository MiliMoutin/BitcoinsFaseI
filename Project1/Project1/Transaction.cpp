#include "Transaction.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

Transaction::Transaction(vector<Input> input, vector<Output> output){
	this->input = input;
	this->output = output;

}

Transaction::Transaction(){

}

bool Transaction::isIDPresent(string id) {
	for (Output o : this->output) {
		if (o.getIdReceiver() == id) {
			return true;
		}
		else {
			return false;
		}
	}
}

