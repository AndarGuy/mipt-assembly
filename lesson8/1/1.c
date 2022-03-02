#include <stdio.h>

int main() {
    int x, y = 25, t = 19;
    int *xp = &t;
    x = *xp;
    *xp = y;
    printf("% d % d\n", x, *xp);
    return 0;
}