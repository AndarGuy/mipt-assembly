; Напишите программу для вычисления формулы d=b-1+a-c. 
; Все числа 3-х байтные целые без знака

global _main

default rel

extern _printf

section .data
output_format   db      "d = %u", 0xA, 0x0
a               dd    8388608
b               dd    7564231
c               dd    9
d               dd    0


section .text

_main:
    push    rbp                     ; save stack

    mov             ax, [b]
    mov             bl, [b + 2]
    dec             ax
    sbb             bl, 0

    mov             cx, [a]
    mov             bh, [a + 2]
    add             ax, cx
    adc             bl, bh

    mov             cx, [c]
    mov             bh, [c + 2]
    sub             ax, cx
    sbb             bl, bh

    mov             [d], ax
    mov             [d + 2], bl

    ; mov ax, [d]
    ; dec ax
    ; mov [d], ax



    ; print
    mov             rdi, output_format
    mov             esi, dword [d]
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit


 