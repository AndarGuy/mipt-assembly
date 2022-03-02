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
y               dd      25
t               dd      19
output_format   db      "%d %d", 0xA, 0

section .bss
x       resd    1

section .text

_main:
    push            rbp
    mov             rbp, rsp

    mov         rax, t              ; *xp=&t;
    mov         edi, dword [rax]    
    mov         [x], edi            ; x = *xp;
    mov         edi, dword [y]      ; *xp = y;
    mov         [rax], edi

    ; print message1
    mov             rdi, output_format
    mov             edx, [rax]
    mov             rsi, [x]
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);

    mov         rsp, rbp
    pop         rbp
    ret


