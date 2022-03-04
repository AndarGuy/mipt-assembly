; 3.asm

global _main

extern _printf

default rel

section .data
string      db      "%02d.%02d", 0xA, 0x0
x           db      0
y           db      0
z           db      220

section .text
_main:
    push    rbp                     ; save stack

    movzx   ax, byte [z]
    mov     bh, 12
    div     bh
    cmp     ah, 0
    jne     a

    mov ah, 12
    dec al

    a: 
    mov byte [y], ah
    mov byte [x], al



    
    mov             rdi, string
    movzx           esi, byte [x]
    movzx           edx, byte [y]
    mov             rax, 0          ; no floating point
    call            _printf
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit
