#include <iostream>
#include <sstream>
#include "crypto_solver.h"

using namespace std;

void crypto::func1(word32* dataBlock) {
	word32 tempWord[3];
	tempWord[0] = tempWord[1] = tempWord[2] = 0;
	for (int i = 0; i < 32; i++) {
		tempWord[0] <<= 1;
		tempWord[1] <<= 1;
		tempWord[2] <<= 1;
		tempWord[0] |= dataBlock[2] & 1;
		tempWord[1] |= dataBlock[1] & 1;
		tempWord[2] |= dataBlock[0] & 1;
		dataBlock[0] >>= 1;
		dataBlock[1] >>= 1;
		dataBlock[2] >>= 1;
	}
	dataBlock[0] = tempWord[0];
	dataBlock[1] = tempWord[1];
	dataBlock[2] = tempWord[2];
}

void crypto::func2(word32* dataBlock) {
	word32 tempWord[3];
	tempWord[0] = (~dataBlock[0]) ^ (~dataBlock[1]) & dataBlock[2];
	tempWord[1] = (~dataBlock[1]) ^ (~dataBlock[2]) & dataBlock[0];
	tempWord[2] = (~dataBlock[2]) ^ (~dataBlock[0]) & dataBlock[1];
	dataBlock[0] = tempWord[0];
	dataBlock[1] = tempWord[1];

	dataBlock[2] = tempWord[2];
} 

void crypto::func3(word32* dataBlock) {
	word32 tempWord[3];
	tempWord[0] = dataBlock[0] ^ (dataBlock[0] >> 16) 
		^ (dataBlock[1] << 16) ^ (dataBlock[1] >> 16) 
		^ (dataBlock[2] << 16) ^ (dataBlock[1] >> 24)
		^ (dataBlock[2] << 8) ^ (dataBlock[2] >> 8) 
		^ (dataBlock[0] << 24) ^ (dataBlock[2] >> 16)
		^ (dataBlock[0] << 16) ^ (dataBlock[2] >> 24) 
		^ (dataBlock[0] << 8);

	tempWord[1] = dataBlock[1] ^ (dataBlock[1] >> 16) 
		^ (dataBlock[2] << 16) ^ (dataBlock[2] >> 16)
		^ (dataBlock[0] << 16) ^ (dataBlock[2] >> 24) 
		^ (dataBlock[0] << 8) ^ (dataBlock[0] >> 8) 
		^ (dataBlock[1] << 24) ^ (dataBlock[0] >> 16)
		^ (dataBlock[1] << 16) ^ (dataBlock[0] >> 24)
		^ (dataBlock[1] << 8);

	tempWord[2] = dataBlock[2] ^ (dataBlock[2] >> 16) 
		^ (dataBlock[0] << 16) ^ (dataBlock[0] >> 16)
		^ (dataBlock[1] << 16) ^ (dataBlock[0] >> 24) 
		^ (dataBlock[1] << 8) ^ (dataBlock[1] >> 8) 
		^ (dataBlock[2] << 24) ^ (dataBlock[1] >> 16)
		^ (dataBlock[2] << 16) ^ (dataBlock[1] >> 24)
		^ (dataBlock[2] << 8);

	dataBlock[0] = tempWord[0];
	dataBlock[1] = tempWord[1];
	dataBlock[2] = tempWord[2];
} 

void crypto::func4(word32* dataBlock) {
	dataBlock[0] = (dataBlock[0] >> 10) ^ (dataBlock[0] << 22);
	dataBlock[2] = (dataBlock[2] << 1) ^ (dataBlock[2] >> 31);
}

void crypto::func5(word32* dataBlock) {
	dataBlock[0] = (dataBlock[0] << 1) ^ (dataBlock[0] >> 31);
	dataBlock[2] = (dataBlock[2] >> 10) ^ (dataBlock[2] << 22);
}

void crypto::func6(word32* dataBlock) {
	func3(dataBlock);
	func4(dataBlock);
	func2(dataBlock);
	func5(dataBlock);
} 

crypto::crypto(word32 key[]) {
	this->key[0] = key[0];
	this->key[1] = key[1];
	this->key[2] = key[2];
}

void crypto::func7(word32 text[]) {
	for(int i = 0; i < 11; i++) {
		text[0] ^= key[0];
		text[1] ^= key[1];
		text[2] ^= key[2];
		func6(text);
	}

	text[0] ^= key[0];
	text[1] ^= key[1];
	text[2] ^= key[2];
	func3(text);
}

void crypto::decryptBlock(word32 text[]) {
	word32 inverseKey[3];
	inverseKey[0] = this->key[0];
	inverseKey[1] = this->key[1];
	inverseKey[2] = this->key[2];
	func3(inverseKey);
	func1(inverseKey);
	func1(text);

	for(int i = 0; i < 11; i++) {
		text[0] ^= inverseKey[0];
		text[1] ^= inverseKey[1];
		text[2] ^= inverseKey[2];
		func6(text);
	}

	text[0] ^= inverseKey[0];
	text[1] ^= inverseKey[1];
	text[2] ^= inverseKey[2];
	func3(text);
	func1(text);
}

void crypto::encrypt(word32 *text, int size) {
	for (int i = 0; i < size/3; i++){
		word32 d[3];
		d[0] = text[i * 3];
		d[1] = text[i * 3 + 1];
		d[2] = text[i * 3 + 2];
		func7(d);
		text[i * 3] = d[0];
		text[i * 3 + 1] = d[1];
		text[i * 3 + 2] = d[2];
	}
}

void crypto::decrypt(word32 *text, int size) {
	for (int i = 0; i < size / 3; i++) {
		word32 d[3];
		d[0] = text[i * 3];
		d[1] = text[i * 3 + 1];
		d[2] = text[i * 3 + 2];
		decryptBlock(d);
		text[i * 3] = d[0];
		text[i * 3 + 1] = d[1];
		text[i * 3 + 2] = d[2];
	}
}
