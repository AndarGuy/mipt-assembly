/*

D: Троичная система счисления

Дано целое число T в троичной системе счисления. Выведите запись числа T в десятичной системе счисления.

*/

#include <stdio.h>

char translate_char(char ch) {
    if (ch > 'A') return ch - 'A' + 10;
    else if (ch > '0') return ch - '0';
    else return ch;
}

from_base(int *s, char base) {
    unsigned long long Y = 0;
    unsigned long long power = 1;
    for (; s != '\0'; s++, power *= base) Y += power * translate_char(s[0]);
    return Y;
}


int main() {

    unsigned long long X = 0;
    scanf("%lld", &X);

    char s[255] = {'0'};
    int number_length = 1;
    int power_of_three = 1;

    unsigned long long Y = 0;

    for (int i = 0; X > 0; i++, power_of_three *= 3) {
        Y += power_of_three * (X % 10);
        X /= 10;
    }

    for (int i = 0; Y > 0; i++, number_length = i) {
        s[i] = '0' + (Y % 10);
        Y /= 10;
    }

    for (int i = 0; i < number_length; i++) {
        printf("%c", s[number_length - i - 1]);
    }

    return 0;

}