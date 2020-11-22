# Отборочный этап Кубка CTF России 2020

## Reverse | Double

### Описание

> Всё, что делает выданная программа — проверяет флаг.
> 
> Если ввести ей верный флаг, она напишет `Correct!`.
> 
> Используйте эту информацию, чтобы решить задание.
> 
> Удачи!

### Выдаваемые файлы

- [double](task/double)

### Решение

Исходник программы: [double.c](task/double.c)

Программа читает `flag` с консоли, затем шифрует его, используя пароли из файлов `password1.txt` и `password2.txt`, и сравнивает с `flag_encrypted`, лежащим в памяти. Нужно найти такой `flag`, который после шифрования окажется равным массиву данных в памяти, то есть, иными словами, нужно расшифровать `flag_encrypted`.

В начале стоит заметить, что в задании использовался несложный анти-отладочный приём, основанный на `ptrace`. Программа пытается себя отладить, и, если не получается, посылает себе `SIGSEGV`, который вызывает её падение.

```c
int checked = 0;

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
```

Чтобы снять анти-отладку, можно, например, удалить вызов этой функции из кода.

Основная сложность задания — распознать, что программа работает с целыми числами размера 128 бит, которые на нижнем уровне представляются как два числа по 64 бита, а в регистрах передаются как `RDX:RAX` (в [реализации gcc](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html)). Сами же эти 128-битные числа используются как многочлены в [поле Галуа](https://ru.wikipedia.org/wiki/Конечное_поле) `GF(2^128)`. В коде также указан элемент поля (`generator`) и образующий многочлен (`minimal_polynomial`):

```c
typedef unsigned __int128 gf_128;

const gf_128 generator = (gf_128)9018875411233164308 + (((gf_128)16934173489065985273) << 64);
const gf_128 minimal_polynomial = (gf_128)16416298200968121579 + (((gf_128)20506921903361606322) << 64);
```

В коде также определены две операции над многочленами:

- операция умножения двух многочленов `a * b`

```c
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
```

- возведение в степень `generator ^ data`, которое используется как кастомный хэш

```c
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
```

Если посчитать мультипликативный порядок `generator`, можно заметить, что он равен `6700417`. Это значит, что у хэша максимум `6700417` различных значений, которые можно перебрать. Получается, что исходные `password1` и `password2` нам вовсе не нужны.

Перейдём к самому шифрованию. В таске использовался немного изменённый [алгоритм XTEA](https://ru.wikipedia.org/wiki/XTEA). В качестве 128-битного ключа использовались элементы `gf_128`:

```c
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
```

Этим алгоритмом флаг был зашифрован дважды. Сначала как ключ был использован хэш от `password1`, затем полученные данные были зашифрованы снова, с использованием хэша от `password2` как ключа:

```c
read_file("password1.txt", password1);
read_file("password2.txt", password2);

gf_128 keys[2] = {
    simple_hash(password1),
    simple_hash(password2)
};

for (i = 0; i < BUFFER_SIZE / (2 * sizeof(uint32_t)); i++) {
    for (j = 0; j < 2; j++) {
        encrypt(ROUNDS, &((uint32_t*)flag)[i * 2], keys[j]);
    }
}
```

Размер буфера для флага равен `64`, и перед вводом флага он зануляется. В коде есть проверка на длину флага: она должна быть равна `51`, значит последние байты буфера останутся нулями. Так как XTEA шифрует по 8 байт, то мы знаем открытый текст последнего блока шифрования: это 8 нулей. Используя это, мы можем применить метод [meet-in-the-middle](https://ru.wikipedia.org/wiki/Метод_встречи_посередине) для того, чтобы найти нужные ключи. Примерный алгоритм на псевдокоде:

```
pt = [0] * 8
ct = encrypt(key2, encrypt(key1, pt))

table = {}

for k in all_possible_keys():
    table[encrypt(k, pt)] = k

for k in all_possible_keys():
    if decrypt(k, ct) in table:
        k1 = table[decrypt(k, ct)]
        k2 = k
        return (k1, k2)
```

Для перебора всех ключей просто будем возводить `generator` во все степени из `[0, 6700417 - 1]`. После того, как ключи будут найдены, останется расшифровать данные в памяти и получить флаг.

__Пример решения: [solver.cpp](task/solver.cpp)__

### Флаг

`ctfcup{1_th1nk_my_sup3r_4nt1_d3bugg1ng_w4s_h4rd...}`
