/*

В агументах командной строки дано целое число А. Выведите запись числа A в двоичном 8-разрядном дополнительном коде.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strrev(char *s) {
    int n = strlen(s);
  
    for (int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

char translate_char(char ch) {
    if (ch == '\n' || ch == ' ')
        return 0;
    if (ch > 'a')
        return ch - 'a' + 10;
    else if (ch > 'A') 
        return ch - 'A' + 10;
    else if (ch > '0') 
        return ch - '0';
    else 
        return 0;
}

int from_base(char *s, char base) {
    unsigned int Y = 0;
    unsigned int power = 1;
    int isNegative = s[0] == '-';
    if (isNegative)
        s++;
    int slen = strlen(s);
    for (int i = 0; i < slen; i++, power *= base) {
        Y += power * translate_char(s[slen - i - 1]);
    }
    return Y * (isNegative ? -1 : 1);
}

int main(int argc, char *argv[]) {

    char result[9] = {0};

    int number;

    scanf("%d", &number);

    if (number < 0) {
        number = 256 + number;
    }

    for (int i = 0; i < 8; i++) {
        result[i] = number % 2 + '0';
        number /= 2;
    }

    strrev(result);

    printf("%s", result);

}