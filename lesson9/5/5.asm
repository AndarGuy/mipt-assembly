; T время в секундах от начала суток, переменной k присвоить значение: T+1. 
; (часы всегда <24)  и выдать на печать в виде чч:мм:сек.

global _main

extern _printf
extern _scanf

default rel

section .data
input_format    db      "%d", 0x0
output_format   db      "%02d:%02d:%02d"

section .bss
t               resw    1

h               resb    1   ; hours
m               resb    1   ; minutes
s               resb    1   ; seconds

section .text
_main:
    push    rbp                     ; save stack

    mov     rdi, qword input_format
    mov     rsi, qword t
    call    _scanf

    
    mov     ax, [t]
    xor     rdx, rdx
    mov     bx, 3600
    div     bx
    mov     [h], al
    mov     [m], dl

    mov     ax, [t]
    mov     bl, 60
    div     bl
    mov     [s], al

    mov             rdi, output_format
    xor             rsi, rsi
    movsx           si, [h]
    xor             rdx, rdx
    movsx           dx, [m]
    xor             rcx, rcx
    movsx           cx, [s]
    mov             rax, 0          ; no floating point
    call            _printf
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit
