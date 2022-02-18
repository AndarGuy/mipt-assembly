// /*
// Дано целое число X в десятичной системе счисления. Выведите запись числа X в восьмеричной системе счисления.

// Ограничения: 0 ≤ X ≤ 1000000000000000000.
// */

// #include <stdio.h>
// #include <fcntl.h>

// int read(int, char*, int);
// int write(int, char*, int);

// int main() {
//     int fdin = open("input.txt", O_RDONLY), fdout = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
//     char input[1024];
//     int data_length = read(fdin, input, 1024);
//     input[data_length] = 0;

//     unsigned long long X;
//     sscanf(input, "%lld", &X);

//     char s[255] = {0};
//     int number_length = 0;

//     for (int i = 0; X > 0; i++, number_length = i) {
//         s[i] = '0' + (X % 8);
//         X /= 8;
//     }

//     for (int i = 0; i < number_length; i++) {
//         write(fdout, s + (number_length - i - 1), 1);
//     }

//     return 0;
// }

#include <stdio.h>
#include <fcntl.h>
 
int read(int, char*, int);
int write(int, char*, int);
 
int main()
{
        int fdin = open("input.txt", O_RDONLY);
        char a[1024];
        int s = read(fdin, a, 1024);
        a[s] = 0;
        int fdout = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
        unsigned long long x, r;
        sscanf(a, "%llu", &x);
        char ans[100];
 
        int i = 0;
        while (x)
        {
                r = x % 8;
                x /= 8;
                ans[i] = '0' + r;
                i++;
        }
        for (int j = i - 1; j >= 0; --j)
                write(fdout, ans + j, 1);
        return 0;
}