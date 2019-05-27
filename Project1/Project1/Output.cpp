#include "Output.h"


Output::Output() {

}

Output::Output(string idReceiver, unsigned long amount) {
	this->idReceiver = idReceiver; 
	this->amount = amount;
}