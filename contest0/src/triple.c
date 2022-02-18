/*

D: Троичная система счисления

Дано целое число T в троичной системе счисления. Выведите запись числа T в десятичной системе счисления.

*/

#include <stdio.h>

char translate_char(char ch) {
    if (ch >= 'A') 
        return ch - 'A' + 10;
    else if (ch >= '0') 
        return ch - '0';
    else 
        return 0;
}

int len(char *s) {
    int counter;
    for (counter = 0; s[0] != 0; s++, counter++);
    return counter;
}

long long from_base(char *s, char base) {
    char is_minus = 0;
    if (s[0] == '-') {
        is_minus = 1;
        s++;
    }
    long long Y = 0;
    long long power = 1;
    int slen = len(s);
    for (int i = 0; i < slen; i++, power *= base) {
        // printf("%lld %lld %d\n", power, Y, translate_char(s[0]));
        Y += power * translate_char(s[slen - i - 1]);
    }
    return is_minus ? -Y : Y;
}

int main() {

    char s[255];
    scanf("%s", s);

    long long Y = from_base(s, 3);

    printf("%lld", Y);

    return 0;

}