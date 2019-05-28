#include "Transaction.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

Transaction::Transaction(Input input, Output output) :output(), input(){
	this->input = input;
	this->output = output;

}

Transaction::Transaction() :output(), input(){

}
