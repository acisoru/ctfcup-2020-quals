#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>

#define ROUNDS 64
#define BUFFER_SIZE 64
#define FLAG_LENGTH 51


typedef unsigned __int128 gf_128;

const gf_128 generator = (gf_128)9018875411233164308 + (((gf_128)16934173489065985273) << 64);
const gf_128 minimal_polynomial = (gf_128)16416298200968121579 + (((gf_128)20506921903361606322) << 64);

char flag[BUFFER_SIZE];
char flag_encrypted[BUFFER_SIZE] = {
    (char)0xd0, (char)0xec, (char)0x22, (char)0x95, (char)0xe4, (char)0xcc, (char)0x6d, (char)0xeb, (char)0x0c, (char)0x1d, (char)0xfc, (char)0x36, (char)0x9b, (char)0x59, (char)0x07, (char)0xa1, (char)0x47, (char)0x01, (char)0x6a, (char)0x5a, (char)0x04, (char)0xd6, (char)0xc1, (char)0xc3, (char)0xa1, (char)0x8e, (char)0xe6, (char)0x12, (char)0x70, (char)0xa8, (char)0x98, (char)0x66, (char)0x40, (char)0x2c, (char)0xff, (char)0x8b, (char)0x80, (char)0x50, (char)0x82, (char)0xbd, (char)0xef, (char)0xbb, (char)0x90, (char)0xb6, (char)0xc5, (char)0x08, (char)0x1c, (char)0x0e, (char)0x94, (char)0x3f, (char)0xbc, (char)0x5f, (char)0xf8, (char)0x38, (char)0xbf, (char)0xf4, (char)0x27, (char)0x1c, (char)0x66, (char)0x1b, (char)0x27, (char)0xdd, (char)0x4b, (char)0xcd
};

int checked = 0;


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
        else {
            a <<= 1;
        }
    }

    return result;
}


gf_128 simple_hash(const char *data) {
    gf_128 temp = generator;
    gf_128 result = 1;
    int i = 0;

    while (*data != NULL) {
        if (((*data) >> i) & 1 == 1) {
            result = gf_128_mul(result, temp);
        }

        temp = gf_128_mul(temp, temp);
        i += 1;

        if (i >= sizeof(char)) {
            data += 1;
            i = 0;
        }
    }

    return result;
}


int anti_debug_helper(int x, int y, int z) {
    return z + (x % y) / y;
}


void anti_debug(void* arg1, void* arg2) {
    if (!checked++ && ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) 
    {
        anti_debug_helper(25, 128, 39);
        __asm ("syscall;");
        __asm ("mov %rax, %rdi;");
        __asm ("mov $11, %rsi;");
        __asm ("mov $62, %rdx;");
        __asm ("call anti_debug_helper;");
        __asm ("syscall;");
    }
}


void encrypt(unsigned int num_rounds, uint32_t v[2], gf_128 key) {
    unsigned int i;
    uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0xDEADBEEF;

    anti_debug(v, &delta);

    for (i = 0; i < num_rounds; i++) {
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + (uint32_t)(key >> (32 * (sum & 3))));
        sum += delta;
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + (uint32_t)(key >> (32 * ((sum>>11) & 3))));
    }
    
    v[0] = v0; v[1] = v1;
}


void read_file(const char *filename, char *ptr) {
    FILE *file;
    size_t size;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror(filename);
        exit(1);
    }

    size = fread(ptr, sizeof(char), BUFFER_SIZE - 1, file);
    ptr[size] = 0;

    fclose(file);
}


int main(int argc, char **argv)
{
    int i, j;
    size_t size;

    char password1[BUFFER_SIZE];
    char password2[BUFFER_SIZE];

    read_file("password1.txt", password1);
    read_file("password2.txt", password2);

    gf_128 keys[2] = {
        simple_hash(password1),
        simple_hash(password2)
    };
    
    puts("Hello! Please input the flag:");
    memset(flag, 0, BUFFER_SIZE);
    size = read(0, flag, BUFFER_SIZE - 1);

    if (flag[size - 1] == '\n') {
        flag[size - 1] = 0;
    }

    if (strlen(flag) != FLAG_LENGTH) {
        puts("Wrong!");
        return 0;
    }

    for (i = 0; i < BUFFER_SIZE / (2 * sizeof(uint32_t)); i++) {
        for (j = 0; j < 2; j++) {
            encrypt(ROUNDS, &((uint32_t*)flag)[i * 2], keys[j]);
        }
    }

    // fwrite(flag, sizeof(char), BUFFER_SIZE, stdout);

    if (!memcmp(flag, flag_encrypted, BUFFER_SIZE)) {
        puts("Correct!");
    }
    else {
        puts("Wrong!");
    }

    return 0;
}
