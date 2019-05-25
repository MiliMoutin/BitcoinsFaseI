#include "Output.h"


Output::Output() {

}

Output::Output(unsigned long idReceiver, unsigned long amount) {
	this->idReceiver = idReceiver; 
	this->amount = amount;
}