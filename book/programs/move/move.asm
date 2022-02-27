; move.asm

default rel

global _main

section .data
    byte_number     db      123
    word_number     dw      12345
    dword_number    dd      1234567890
    qword_number1   dq      1234567890123456789
    qword_number2   dq      123456
    qword_number3   dq      3.14

section .bss

section .text
_main:
    push        rbp
    mov         rbp, rsp

    mov         rax, -1                     ; fill rax with 1s
    mov         al, byte [byte_number]      ; does NOT clear upper bits of rax
    xor         rax, rax                    ; clear rax
    mov         al, byte [byte_number]      ; now rax has the correct value

    mov         rax, -1                     ; fill rax with 1s
    mov         ax, word [word_number]      ; does NOT clear upper bits of rax
    xor         rax,rax                     ; clear rax
    mov         ax, word [word_number]      ; now rax has the correct value

    mov         rax, -1                     ; fill rax with 1s
    mov         eax, dword [dword_number]   ; does clear upper bits of rax

    mov         rax, -1                     ; fill rax with 1s
    mov         rax, qword [qword_number1]  ; does clear upper bits of rax
    mov         qword [qword_number2], rax  ; one operand always a register
    mov         rax, 123456                 ; source operand an immediate value
    movq        xmm0, [qword_number3]       ; instruction for floating point

    mov         rsp,rbp
    pop         rbp
    ret