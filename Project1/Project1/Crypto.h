#pragma once
#include <iostream>
#include "../cryptopp820/cryptlib.h"
#include "../cryptopp820/ecp.h"
#include "../cryptopp820/eccrypto.h"
#include "../cryptopp820/hex.h"
#include "../cryptopp820/oids.h"
#include "../cryptopp820/osrng.h"

using namespace CryptoPP;
using namespace std;

#define PRIVATE_KEY_CHARS 32
#define PUBLIC_KEY_CHARS 64

class Crypto {
public:
	ECDSA<ECP, SHA256>::PrivateKey generatePrivKey();
	vector<byte> getSignature(ECDSA<ECP, SHA256>::PrivateKey &privKey, string &data);
	bool verifySignature(ECDSA<ECP, SHA256>::PublicKey &pubKey, string &data, vector<byte> &signature);
	string hexPrint(vector<byte> &dataToPrint);
	string getPI(ECDSA<ECP, SHA256>::PublicKey &pubKey);
	string hashSHA256(string& message);
};