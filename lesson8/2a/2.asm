; 1.asm

; Напишите программу на ассемблере, которая соответствует приведенному коду на С.

; int  x, y=25, t=19;
; int *xp=&t;
;            x = *xp;
; *xp = y;
; printf(“%d   %d\n”, x, *xp);

global _main

default rel

extern _printf

section .data
a               db      12
b               dd      120
output_format   db      "%d", 0xA, 0x0

section .text

_main:
    push            rbp
    mov             rbp, rsp

    mov             rax, [a]
    mov             [b], al

    ; print
    mov             rdi, output_format
    mov             rsi, [b]
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);

    mov         rsp, rbp
    pop         rbp
    ret


