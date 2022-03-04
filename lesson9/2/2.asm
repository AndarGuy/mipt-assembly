; 2.asm

global _main

extern _printf

default rel

section .data
string      db      "Done!", 0xA, 0x0

section .bss
z           resq    1

section .text
_main:
    push    rbp                     ; save stack
    
    mov rax, a
    jmp rax

    c: 
    mov rax, b
    mov [z], rax
    jmp qword [z]

    a:
    mov rax, c
    mov [z], rax
    mov rbx, [z]
    jmp rbx

    b: 
    mov             rdi, string
    mov             rax, 0          ; no floating point
    call            _printf
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit
