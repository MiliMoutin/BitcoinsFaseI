#include "Node.h"
#include <vector>
#include "Input.h"
#include "Output.h"

bool Node::operator==(Node* node) {
	if (node->getPublicID() == this->publicID) {
		return true;
	}
}

void Node::createPPKey() {


}

void Node::makeTx(string publicId, double EDACoins) {
	if (canDoTx(EDACoins)) {
		/*En collector voy a guardar las transacciones necesarias*/
		list<UTXO> collector;
		double amountCollected = 0;
		list<UTXO>::iterator ptr;

		/*Busco UTXO hasta que llegue al monto que quiero*/
		for (ptr = UTXOs.begin(); ptr != UTXOs.end() && amountCollected < EDACoins; ptr++) {
			amountCollected += ptr->getAmount();
			collector.push_back(*ptr);
		}

		//ACA FIRMAMOS
		string Signature = "";
		/*Ahora creo la transacción*/
		/*Primero creo lo vector de input y outputs*/
		amountCollected = EDACoins;
		vector<Input> impColector;
		vector<Output> outColector;
		for (UTXO u : collector) {
			if (u.getAmount() >= amountCollected) {
				impColector.push_back(Input("blouesin", u.getUTXOId(), Signature));
				outColector.push_back(Output(publicID, amountCollected));
				/*Si la UXTO es más grande, entocnes me mando a mi mismo lo que sobra*/
				impColector.push_back(Input("bloquesin", u.getUTXOId(), Signature));
				outColector.push_back(Output(this->publicID, amountCollected - u.getAmount()));
			}
			else {
				impColector.push_back(Input("bloquesin", u.getUTXOId(), Signature));
				outColector.push_back(Output(publicID, u.getAmount()));
				amountCollected - u.getAmount();
			}
		}
		this->to_send = Transaction(impColector, outColector);
	}
}


bool Node::canDoTx(double amount) {
	double amountCollected = 0;
	list<UTXO>::iterator ptr;
	bool found = false;
	for (ptr = UTXOs.begin(); ptr != UTXOs.end() && !found; ptr++) {
		amountCollected += ptr->getAmount();
		if (amountCollected >= amount) {
			found = true;
		}
	}
	return found;
}

