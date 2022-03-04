; 3.asm

global _main

extern _printf
extern _scanf

default rel

section .data
input_format    db      "%d", 0x0
yes             db      "YES", 0xA, 0x0
no              db      "NO", 0xA, 0x0
x               dw      23456

section .text
_main:
    push    rbp                     ; save stack

    mov     rdi, qword input_format
    mov     rsi, qword x
    call    _scanf
    
    mov     ax, [x]
    to_cycle:
    xor     rdx, rdx
    mov     bx, 10
    div     bx
    cmp     dx, 5
    je      to_yes
    cmp     ax, 0
    jne     to_cycle

    jmp     to_no
    to_yes:
    mov     rdi, yes
    jmp     to_print
    to_no:
    mov     rdi, no
    
    to_print:
    mov             rax, 0          ; no floating point
    call            _printf
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit
