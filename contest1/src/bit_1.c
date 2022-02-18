/*

В одном байте закодирована следующая информация (от младших бит к старшим):

Ширина (бит)	Признак	Возможные значения	Условные сокращения
1	пол	1 - male, 0 - female	ma, fe
1	умный	1 - clever, 0 - dummy	cl, du
1	шляпа	1 - hat, 0 - without hat	ha, nh
1	брюки-юбка	1 - trousers, 0 - skirt	tr, sk
2	цвет волос	00 - blonde, 01 - red, 10 - brown, 11 - black	bn, rd, bw,bk
2	цвет глаз	00 - blue, 01 - green, 10 - gray, 11 - dark	bu, ge, gy, da
Например, 0x6B, в бинарном виде 0110 1011 (читаем от младших бит к старшим) - (1) - мужчина, (1) - умный, (0) - без шляпы, (1) - в брюках, (10) - шатен (цвет волос - brown), (01) - зеленоглазый.
Можно написать аббревиатурами: ma cl nh tr bw ge

По входному числу выясните - женщина это или мужчина

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char translate_char(char ch) {
    if (ch > 'a')
        return ch - 'a' + 10;
    if (ch > 'A') 
        return ch - 'A' + 10;
    else if (ch > '0') 
        return ch - '0';
    else 
        return 0;
}

char translate_number(unsigned char number) {
    if (number > 9) 
        return 'A' + number - 10;
    return '0' + number;
}

unsigned int from_base(char *s, char base) {
    unsigned int Y = 0;
    unsigned int power = 1;
    int slen = strlen(s);
    for (int i = 0; i < slen; i++, power *= base) {
        Y += power * translate_char(s[slen - i - 1]);
    }
    return Y;
}

char *to_base(unsigned int number, char base) {
    char *Y = (char *) malloc(64);
    for (int counter = 0; number > 0; counter++, number /= base) {
        Y[counter] = translate_number(number % base);
    }
    return Y;
}

int main(int argc, char *argv[]) {

    char *s = argv[1];
    unsigned int number = from_base(s, 16);
    char *conveted = to_base(number, 2);
    printf("%s", conveted[0] - '0' ? "ma" : "fe");

    free(conveted);
    
    return 0;
}