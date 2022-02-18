/*

Переведите число, записанное в шестнадцатиричной системе счисления, в двоичную.

Входные данные: неотрицательное шестнадцатиричное число, содержащее не более 1000000 цифр (0123456789ABCDEF).

Единственная строка выходных данных должна содержать последовательность 0 и 1, образующих двоичную запись числа, полученного на входе. Лидирующих нулей быть не должно.

*/

#include <stdio.h>
#include <stdlib.h>

const char *i0 = "0000";
const char *i1 = "0001";
const char *i2 = "0010";
const char *i3 = "0011";
const char *i4 = "0100";
const char *i5 = "0101";
const char *i6 = "0110";
const char *i7 = "0111";
const char *i8 = "1000";
const char *i9 = "1001";
const char *iA = "1010";
const char *iB = "1011";
const char *iC = "1100";
const char *iD = "1101";
const char *iE = "1110";
const char *iF = "1111";

const char *hex_to_bin(char ch) {
    switch (ch) {
        case '0':
            return i0;
        case '1':
            return i1;
        case '2':
            return i2;
        case '3':
            return i3;
        case '4':
            return i4;
        case '5':
            return i5;
        case '6':
            return i6;
        case '7':
            return i7;
        case '8':
            return i8;
        case '9':
            return i9;
        case 'A':
            return iA;
        case 'B':
            return iB;
        case 'C':
            return iC;
        case 'D':
            return iD;
        case 'E':
            return iE;
        case 'F':
            return iF;
    }
    return i0;
}

int main() {
    char *s = calloc(1000000 * 4 + 10, 1);
    scanf("%s", s);

    char *r = calloc(1000000 * 4 + 10, 1); 
    for (int i = 0; s[i] != 0; i++) {
        const char *bin = hex_to_bin(s[i]);
        for (int j = 0; j < 4; j++) {
            r[i * 4 + j] = bin[j];
        }
        r[i * 4 + 5] = 0;
    }

    int margin = 0;

    for (margin = 0; r[margin] != '1' && r[margin + 1] != 0 && r[margin] != 0; margin++); 

    printf("%s", r + margin);

    free(s);
    free(r);

    return 0;
}