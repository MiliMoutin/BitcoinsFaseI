#include "Node.h"
#include <vector>
#include "Input.h"
#include "Output.h"

using namespace CryptoPP;



bool Node::operator==(Node* node) {
	if (node->getPublicID() == publicId) {
		return true;
	}
}

void Node::createPPKey() {
	this->privateKey = crypp.generatePrivKey();
	ECDSA<ECP, SHA256>::PublicKey pubk;
	this->privateKey.MakePublicKey(pubk);
	this->publicKey = pubk;
	this->publicId = crypp.getPI(this->publicKey);
}

Transaction& Node::signTx(Transaction& t) {

	for (Input& i: t.getInput()) {

		AutoSeededRandomPool prng;
		string message = i.toSign();
		vector<byte> vecby=crypp.getSignature(this->privateKey, message);
		i.setSignature(vecby);
	}
	return t;

}

void Node::makeTx(string pID, double EDACoins) {
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

		/*Ahora creo la transacción*/
		/*Primero creo lo vector de input y outputs*/
		amountCollected = EDACoins;
		vector<Input> impColector;
		vector<Output> outColector;
		for (UTXO u : collector) {
			if (u.getAmount() >= amountCollected) {
				impColector.push_back(Input("blouesin", u.getUTXOId()));
				outColector.push_back(Output(pID, amountCollected));
				/*Si la UXTO es más grande, entocnes me mando a mi mismo lo que sobra*/
				impColector.push_back(Input("bloquesin", u.getUTXOId()));
				outColector.push_back(Output(pID, amountCollected - u.getAmount()));
			}
			else {
				impColector.push_back(Input("bloquesin", u.getUTXOId()));
				outColector.push_back(Output(publicId, u.getAmount()));
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

bool Node::verifyTx(Transaction& t, string publicID) {
	/*
	vector<Input>::iterator in;
	vector<Output>::iterator out;
	for (in = t.getInput().begin, out = t.getOutputs().begin(); in != t.getInput().end() && out != t.getOutputs().end(); in++, out++) {
		if(this->crypp.verifySignature())
	}
	*/
	return true;
}
