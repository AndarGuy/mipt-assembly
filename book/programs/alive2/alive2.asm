; alive2.asm

global _main

default rel

extern _printf

section .data
    message1            db      "Hello, World!", 0  
    message2            db      "Alive and Kicking!", 0
    radius              dq      357
    pi                  dq      3.14
    string_format       db      "%s", 10, 0                 ; format for printing a string
    float_format        db      "%lf", 10, 0                ; format for printing a float
    int_format          db      "%d", 10, 0                 ; format for printing an int

section .bss

section .text
_main:
    push            rbp
    mov             rbp, rsp

    ; print message1
    mov             rdi, string_format
    mov             rsi, message1
    mov             rax, 0                  ; no floating point
    call            _printf

    ; print message2
    mov             rdi, string_format
    mov             rsi, message2
    mov             rax, 0                  ; no floating point
    call            _printf

    ; print radius
    mov             rdi, int_format
    mov             rsi, [radius]
    mov             rax, 0                  ; no floating point
    call            _printf

    ; print pi
    mov             rdi, float_format
    movq            xmm0, [pi]
    mov             rax, 1                  ; 1 xmm register used
    call            _printf

    mov             rsp, rbp
    pop             rbp
    ret                                     ; exit

    

