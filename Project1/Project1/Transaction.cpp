#include "Transaction.h"

Transaction::Transaction(Input input, Output output) :output(), input(){
	this->input = input;
	this->output = output;
}

Transaction::Transaction() :output(), input(){

}