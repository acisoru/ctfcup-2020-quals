#include <iostream>
#include <cstdint>
#include "crypto_solver.h"

using namespace std;

int main()
{
    word32 key[3] = {0xdeadb33f, 0x13378bcd, 0xd1cded};
    crypto way(key);
    
	word32 check[] = { 0x684f3223, 0x7a554d47, 0x2abae4d9, 0x6f5b207c,
        0x5236549, 0xd5a8cdce, 0xe36a5a95, 0x80f05e73, 
        0x272d1ec8, 0xe0769ea1, 0x70b0dc1, 0xab3724f7,
        0x4f219b7, 0x98e3e8ef, 0xadb34795, 0xd23ed685, 
        0xb3a39279, 0xe88f9dd7, 0xc3894483, 0xe1202b0f, 
        0x594a9a6d, 0x2996b6fb, 0xc2475c06, 0x5a8fa266, 
        0xeb44c510, 0xa018b38e, 0xe1ea7efe, 0xc36aa3eb, 
        0xfe81eca3, 0x2367de1, 0x8af50058, 0xd4807d58, 
        0x16a19d1f, 0x96aeb137, 0xe5ae23c7, 0x55973551 };
    way.decrypt(check, 36);
	for (int i = 0; i < 36; i++){
		cout << (char)(check[i] & 0xff);
	}
	cout << endl;
	return 0;
}
