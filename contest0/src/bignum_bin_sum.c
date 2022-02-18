/*

B: Сумма больших двоичных чисел

Напишите программу, которая суммирует большие натуральные числа, заданные в двоичной системе счисления.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int len(char *s) {
    int counter;
    for (counter = 0; s[0] != 0; s++, counter++);
    return counter;
}

int main() {
    char *a = calloc(4048, 1), *b = calloc(4048, 1), *r = calloc(4048, 1);
    scanf("%s%s", a, b);
    int a_len = len(a), b_len = len(b);
    int max_len = a_len > b_len ? a_len : b_len;
    max_len++;
    r[0] = '0';

    int mod = 0;
    for (int ap = a_len - 1, bp = b_len - 1, i = 0; ap >= 0 || bp >= 0 || mod > 0; ap--, bp--, i++) {
        if (ap >= 0 && bp >= 0) {
            r[max_len - i - 1] = (a[ap] - '0') + (b[bp] - '0') + mod;
        } else if (ap >= 0) {
            r[max_len - i - 1] = (a[ap] - '0') + mod;
        } else if (bp >= 0) {
            r[max_len - i - 1] = (b[bp] - '0') + mod;
        } else if (mod > 0) {
            r[max_len - i - 1] = mod;
        } else {
            break;
        }

        // printf("%d\n", i);

        mod = r[max_len - i - 1] / 2;
        r[max_len - i - 1] %= 2;
        r[max_len - i - 1] += '0';

    }

    int margin = 0;

    for (margin = 0; r[margin] != '1' && r[margin + 1] != 0 && r[margin] != 0; margin++); 

    printf("%s", r + margin);

    free(a);
    free(b);
    free(r);
    

}