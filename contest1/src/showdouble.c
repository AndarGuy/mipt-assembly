/*

Действительное число
Напишите программу, которая получает на вход слово "float", "double" или "long double", после которого идёт действительное число. и выводит его бинарное представление по 4 разряда

Вход	Выход
float 1	0011 1111 1000 0000 0000 0000 0000 0000
double 2	0100 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
long double -1	0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1011 1111 1111 1111 1000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c %c%c%c%c"
#define BYTE_TO_BINARY(byte) (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0') 

typedef union {
    float f;
    unsigned char bytes[sizeof(float)]; // 4
} TFloat;
 
typedef union {
    double d;
    unsigned char bytes[sizeof(double)]; // 8
} TDouble;

typedef union {
    long double ld;
    unsigned char bytes[16]; // 16
} TLongDouble;

int main() {
    int size = 0;
    char *type = calloc(16, sizeof(char)), *temp = calloc(16, sizeof(char));
    scanf("%s", type);

    if (!strcmp(type, "long")) {
        scanf("%s", temp);
    }

    if (!strcmp(type, "long")) {
        size = 16;
        long double x;
        scanf("%Lf", &x);
        TLongDouble data;
        data.ld = x;

        for (int i = 0; i < size; i++) {
            char n = data.bytes[size - i - 1];
            if (i < 6) n = 0;
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(n));
            printf(" ");
        }


    } else if (!strcmp(type, "double")) {
        size = 8;
        double x;
        scanf("%lf", &x);
        TDouble data;
        data.d = x;

        for (int i = 0; i < size; i++) {
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(data.bytes[size - i - 1]));
            printf(" ");
        }

    } else {
        size = 4;
        float x;
        scanf("%f", &x);
        TFloat data;
        data.f = x;

        for (int i = 0; i < size; i++) {
            printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(data.bytes[size - i - 1]));
            printf(" ");
        }
    }

    free(type);
    free(temp);

    return 0;

}