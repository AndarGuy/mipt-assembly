/*

На стандартном потоке ввода подается последовательно вещественное число x и целое число в 16-ричной записи y. 
Единственным аргументов программы является целое число z в 27-ричной системе исчисления. 
Необходимо вывести вычислить значение x+y+z и вывести его на стандартный поток вывода с точностью до 3-го знака после точки.

*/

#include <stdio.h>

char translate_char(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 10;
    } else if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 10;
    } else if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    
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

int main(int argc, char *argv[]) {
    if (argc < 2) 
        return 1;
    float x;
    scanf("%f", &x);
    long long y, z;
    // printf("%s\n", argv[0]);
    z = from_base(argv[1], 27);
    // printf("%lld\n", z);
    char z_string[255];
    scanf("%s", z_string);
    y = from_base(z_string, 16);
    // printf("%lld\n", y);

    printf("%lf\n", x + y + z);

    return 0;
}