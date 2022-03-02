; Напишите программу для вычисления формулы d=b-1+a-c. 
; Все числа 3-х байтные целые без знака

global _main

default rel

extern _printf

output_format   db      "z = %d", 0xA, 0x0

section .bss
a               resb    3
b               resb    3
c               resb    3
d               resb    3

section .text

_main:
    push    rbp                     ; save stack


    ; print
    mov             rdi, output_format
    movsx           esi, word [z]
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit


 