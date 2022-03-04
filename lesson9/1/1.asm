; 1.asm

global _main

extern _printf

section .data
    string      db      "Done!", 0xA, 0x0

section .text
_main:
    push    rbp                     ; save stack

    jmp short a

    c: 
    jmp short b

    a: 
    jmp short c

    b: 
    mov             rdi, string
    mov             rax, 0          ; no floating point
    call            _printf
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit
