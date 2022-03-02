; Реализовать присваивание b = a; (не более двух команд) при условии:
; char a; short b

global _main

default rel

extern _printf

section .data
x               dd      -2147483645
y               dd      2147483640
z               dd      4294967293

output_format   db      "x = %d, y = %d, z = %u", 0xA, 0x0

section .text

_main:
    push    rbp                     ; save stack

    mov al, byte [x]
    inc al
    mov byte [x], al

    mov al, byte [y]
    inc al
    mov byte [y], al

    mov al, byte [z]
    inc al
    mov byte [z], al

    xor rax, rax

    ; print
    mov             rdi, output_format
    mov             rsi, [x]
    mov             rdx, [y]
    mov             rcx, [z]
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);
  
    pop	rbp                         ; restore stack
    ret                             ; exit


 