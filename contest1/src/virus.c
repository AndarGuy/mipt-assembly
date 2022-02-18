/*

Недалёкое будущее. У Вас оказалось n нанороботов, каждый из которых имеет свой номер (нумерация начинается с 0) и программу. 
Известно, что v из них заражены нановирусом для нанороботов (говорят, что автор пользовался для написания исходного кода этого вируса текстовым редактором nano). 
Нановирус размножается по такому алгоритму: если он работает на нанороботе номер X, то он заражает нанороботов с номерами X*2, X*3+1, X*4+3, X*5+6... 
(при каждом заражении разница номеров между подряд идущими заражёнными увеличивается на 1). 
С вновь заражённых нанороботов вирус уже никуда не распространяется (см. ответ к примеру). 
И теперь нужно подсчитать: сколько же у Вас заражённых нанороботов?

*/

#include <stdio.h>
#include <stdlib.h>

int comparator(void *a, void *b) {
    int *c = (int *) a, *d = (int *) b;
    return *c < *d;
}

void set_bit(char *robots, unsigned int bit) {
    robots[bit / 8] = robots[bit / 8] | (1 << (bit % 8));
}

int count_bits(char chunk) {
    int counter = 0;
    while (chunk) {
        chunk = chunk & (chunk - 1);
        counter++;
    }
    return counter;
}

int main() {
    unsigned int v, n;

    scanf("%d%d", &v, &n);

    char *robots = (char *) calloc(12500001, sizeof(char));

    unsigned int *infected = calloc(v, sizeof(unsigned int));

    for (unsigned int i = 0; i < v; i++) {
        scanf("%d", infected + i);
    }

    for (unsigned int i = 0; i < v; i++) {
        unsigned int inf = infected[i];
        for (unsigned long pointer = inf, multiplier = 2, increment = 0, increment_ = 1; pointer < n; pointer = inf * multiplier + increment, multiplier++, increment += increment_, increment_++) {
            set_bit(robots, pointer);
        }
    }

    unsigned int result = 0;

    for (unsigned long i = 0; i < n / 8 + 1; i++) {
        result += count_bits(robots[i]);
    }


    printf("%d", result);

    free(robots);
    free(infected);

    return 0;
}