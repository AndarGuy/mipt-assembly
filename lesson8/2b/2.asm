; Реализовать присваивание b = a; (не более двух команд) при условии:
; char a; short b

global _main

default rel

extern _printf

section .data
a               db      -1
b               dd      120
output_format   db      "%d", 0xA, 0x0

section .text

_main:
    push    rbp                     ; save stack

    movsx           eax, byte [a]
    mov             [b], eax

    ; print
    mov             rdi, output_format
    mov             rsi, [b]
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);
  
    pop	rbp                         ; restore stack
    ret                             ; exit


 