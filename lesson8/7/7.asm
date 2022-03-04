; Умножить слово на байт

global _main

default rel

extern _printf

section .data
output_format   db      "result = %u", 0xA, 0x0
a               dw      1000
b               db      50

section .text

_main:
    push    rbp                     ; save stack

    mov     cx, word [a]
    movzx   bx, byte [b]
    movzx   ax, cl
    mul     bl
    mov     dx, ax
    movzx   ax, ch
    mul     bl
    add     dh, al
    movzx   edx, dx


    ; print
    mov             rdi, output_format
    mov             esi, edx
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit


 