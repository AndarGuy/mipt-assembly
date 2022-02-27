; hello4.asm

global _main

extern      _printf                                         ; declare the function as external

section .data
    message         db  "Hello, World!", 0
    string_format   db  "This is out string: %s", 10, 0     ; print format

section .bss

section .text
_main:
    push            rbp
    mov             rbp, rsp
    mov             rdi, string_format      ; first argument for printf
    mov             rsi, message            ; second argument for printf
    mov             rax, 0                  ; no xmm registers involved
    call            _printf                  ; call the function

    mov             rsp, rbp
    pop             rbp
    mov             rax, 0x2000000 + 1      ; 1 = exit
    mov             rdi, 0                  ; 0 = successful exit code
    syscall                                 ; exit
