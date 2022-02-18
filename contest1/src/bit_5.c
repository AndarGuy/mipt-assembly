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

Следователь опросил нескольких свидетелей и аббревиатурой записал их описание подозреваемого. Нужно закодировать описание подозреваемого одним числом. Внимание! Так как свидетелей было несколько, одна и та же характеристика может быть перечислена несколько раз. Характеристика не может изменяться от свидетеля к свидетелю, т.е. голубоглазый блондин не станет темноглазым брюнетом.

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
        return 'a' + number - 10;
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

void strrev(char *s) {
    int n = strlen(s);
  
    for (int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

char *to_base(unsigned int number, char base) {
    char *Y = (char *) calloc(64, sizeof(char));
    for (int counter = 0; number > 0; counter++, number /= base) {
        Y[counter] = translate_number(number % base);
    }
    strrev(Y);
    return Y;
}

int main(int argc, char *argv[]) {

    char s[9] = {0};

    char params[128];
    fgets(params, 127, stdin);
    int len = strlen(params);
    int i = 0;
    char param[3];

    while (1) {
        param[0] = params[i++];
        param[1] = params[i++];
        param[2] = 0;

        if (!strcmp(param, "ma")) {
            s[7] = '1';
        } else if (!strcmp(param, "fe")) {
            s[7] = '0';
        } else if (!strcmp(param, "cl")) {
            s[6] = '1';
        } else if (!strcmp(param, "du")) {
            s[6] = '0';
        } else if (!strcmp(param, "ha")) {
            s[5] = '1';
        } else if (!strcmp(param, "nh")) {
            s[5] = '0';
        } else if (!strcmp(param, "tr")) {
            s[4] = '1';
        } else if (!strcmp(param, "sk")) {
            s[4] = '0';
        } else if (!strcmp(param, "bn")) {
            s[3] = '0';
            s[2] = '0';
        } else if (!strcmp(param, "rd")) {
            s[3] = '1';
            s[2] = '0';
        } else if (!strcmp(param, "bw")) {
            s[3] = '0';
            s[2] = '1';
        } else if (!strcmp(param, "bk")) {
            s[3] = '1';
            s[2] = '1';
        } else if (!strcmp(param, "bu")) {
            s[1] = '0';
            s[0] = '0';
        } else if (!strcmp(param, "ge")) {
            s[1] = '1';
            s[0] = '0';
        } else if (!strcmp(param, "gy")) {
            s[1] = '0';
            s[0] = '1';
        } else if (!strcmp(param, "da")) {
            s[1] = '1';
            s[0] = '1';
        }

        if (++i >= len) {
            break;
        }
    }

    unsigned int number = from_base(s, 2);
    // printf("%d\n", number);
    char *conveted = to_base(number, 16);
    // printf("%s\n", s);
    printf("%s\n", conveted);

    free(conveted);

    return 0;
}