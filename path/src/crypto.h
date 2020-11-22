#include <cstdint>

using word32 = uint32_t;
using byte = uint8_t;

#pragma once
class crypto
{
public:
	crypto(word32 key[]);

	void encrypt(word32* text, int size);
	//void decrypt(word32* text, int size);

private:
	void func1(word32* dataBlock);
	void func2(word32* dataBlock);
	void func3(word32* dataBlock);
	void func4(word32* dataBlock);
	void func5(word32* dataBlock);
	void func6(word32* dataBlock);

	word32 key[3];

	void func7(word32 text[]);
	//void decryptBlock(word32 text[]);
};