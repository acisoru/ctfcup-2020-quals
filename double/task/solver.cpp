#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <map>

#define ROUNDS 64
#define BUFFER_SIZE 64


typedef unsigned __int128 gf_128;

/* x^127 + x^126 + x^125 + x^123 + x^121 + x^120 + x^113 + x^110 + x^106 + x^104 + x^100 + x^96 + x^93 + x^92 + x^90 + x^87 + x^84 + x^83 + x^82 + x^80 + x^79 + x^74 + x^71 + x^70 + x^69 + x^68 + x^67 + x^64 + x^62 + x^61 + x^60 + x^59 + x^58 + x^56 + x^53 + x^51 + x^48 + x^46 + x^45 + x^44 + x^43 + x^41 + x^40 + x^38 + x^37 + x^34 + x^33 + x^32 + x^27 + x^19 + x^18 + x^17 + x^15 + x^14 + x^11 + x^10 + x^4 + x^2 */
const gf_128 generator = (gf_128)9018875411233164308 + (((gf_128)16934173489065985273) << 64);

/* x^128 + x^124 + x^123 + x^122 + x^119 + x^116 + x^114 + x^113 + x^112 + x^109 + x^108 + x^107 + x^103 + x^102 + x^100 + x^97 + x^92 + x^91 + x^90 + x^89 + x^87 + x^83 + x^81 + x^80 + x^79 + x^78 + x^73 + x^71 + x^69 + x^68 + x^65 + x^63 + x^62 + x^61 + x^57 + x^56 + x^55 + x^54 + x^52 + x^49 + x^46 + x^45 + x^43 + x^37 + x^36 + x^35 + x^34 + x^31 + x^27 + x^25 + x^24 + x^23 + x^20 + x^18 + x^17 + x^15 + x^14 + x^11 + x^10 + x^7 + x^6 + x^5 + x^3 + x + 1 */
const gf_128 minimal_polynomial = (gf_128)16416298200968121579 + (((gf_128)20506921903361606322) << 64);

static char flag_encrypted[BUFFER_SIZE] = {
    (char)0xd0, (char)0xec, (char)0x22, (char)0x95, (char)0xe4, (char)0xcc, (char)0x6d, (char)0xeb, (char)0x0c, (char)0x1d, (char)0xfc, (char)0x36, (char)0x9b, (char)0x59, (char)0x07, (char)0xa1, (char)0x47, (char)0x01, (char)0x6a, (char)0x5a, (char)0x04, (char)0xd6, (char)0xc1, (char)0xc3, (char)0xa1, (char)0x8e, (char)0xe6, (char)0x12, (char)0x70, (char)0xa8, (char)0x98, (char)0x66, (char)0x40, (char)0x2c, (char)0xff, (char)0x8b, (char)0x80, (char)0x50, (char)0x82, (char)0xbd, (char)0xef, (char)0xbb, (char)0x90, (char)0xb6, (char)0xc5, (char)0x08, (char)0x1c, (char)0x0e, (char)0x94, (char)0x3f, (char)0xbc, (char)0x5f, (char)0xf8, (char)0x38, (char)0xbf, (char)0xf4, (char)0x27, (char)0x1c, (char)0x66, (char)0x1b, (char)0x27, (char)0xdd, (char)0x4b, (char)0xcd
};


gf_128 gf_128_mul(gf_128 a, gf_128 b)
{
    gf_128 result = 0;
    
    for (; b; b >>= 1) {
        if (b & 1 == 1) {
            result ^= a;
        }

        if ((a >> 64) & 0x8000000000000000)
        {
            a = (a << 1) ^ minimal_polynomial;
        }
        else
        {
            a <<= 1;
        }
    }

    return result;
}


/* based on public domain implementation from https://en.wikipedia.org/wiki/XTEA */
void encrypt(unsigned int num_rounds, uint32_t v[2], unsigned __int128 key) {
    unsigned int i;
    uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0xDEADBEEF;

    for (i = 0; i < num_rounds; i++) {
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + (uint32_t)(key >> (32 * (sum & 3))));
        sum += delta;
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + (uint32_t)(key >> (32 * ((sum>>11) & 3))));
    }
    
    v[0] = v0; v[1] = v1;
}


/* based on public domain implementation from https://en.wikipedia.org/wiki/XTEA */
void decrypt(unsigned int num_rounds, uint32_t v[2], unsigned __int128 key) {
    unsigned int i;
    uint32_t v0 = v[0], v1 = v[1], delta = 0xDEADBEEF, sum = delta*num_rounds;

    for (i = 0; i < num_rounds; i++) {
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + (uint32_t)(key >> (32 * ((sum>>11) & 3))));
        sum -= delta;
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + (uint32_t)(key >> (32 * (sum & 3))));
    }
    
    v[0] = v0; v[1] = v1;
}


int main(int argc, char **argv) {
    std::map<uint64_t, gf_128> table;

    int i, j, k;
    gf_128 h = 1;

    int g_order = 6700417;

    uint32_t _pt[2] = {0, 0};
    uint32_t _ct[2] = {0, 0};

    _ct[0] = ((uint32_t*)flag_encrypted)[14];
    _ct[1] = ((uint32_t*)flag_encrypted)[15];

    /* meet in the middle */
    
    for (i = 0; i < g_order; i++) {
        if (i % 10000 == 0) { 
            printf("%d\n", i);
        }
        
        uint32_t ct[2] = {_pt[0], _pt[1]};
        encrypt(64, ct, h);
        table[((uint64_t)(ct[0]) << 32) + (uint64_t)(ct[1])] = h;
        h = gf_128_mul(h, generator);
    }

    h = 1;

    for (i = 0; i < g_order; i++) {
        if (i % 10000 == 0) { 
            printf("%d\n", i);
        }

        uint32_t pt[2] = {_ct[0], _ct[1]};
        decrypt(64, pt, h);
        std::map<uint64_t, gf_128>::iterator iter = table.find(((uint64_t)(pt[0]) << 32) + (uint64_t)(pt[1]));
        if (iter != table.end()) {
            gf_128 keys[2] = {h, iter->second};
            for (j = 0; j < BUFFER_SIZE / (2 * sizeof(uint32_t)); j++) {
                for (k = 0; k < 2; k++) {
                    decrypt(ROUNDS, &((uint32_t*)flag_encrypted)[j * 2], keys[k]);
                }
            }
            puts(flag_encrypted);

            break;
        }
        h = gf_128_mul(h, generator);
    }

    return 0;
}
