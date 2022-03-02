; Вычислить значение z

; z=10*a/(a+b)+10*b/(c+d)

; a, b, c – байт
; d        - слово

global _main

default rel

extern _printf

section .data
a               db      70
b               db      3
c               db      10
d               dw      1000

output_format   db      "z = %d", 0xA, 0x0

section .bss
z               resw    1

section .text

_main:
    push    rbp                     ; save stack

    mov     [z], word 0x0           ; z = 0
    
    xor     ax, ax                  ; clean ax
    mov     al, [a]                 ; ax = a
    mov     bx, 10                  ; bx = 10
    imul    bx                      ; dx:ax = ax * bx
    
    xor     bx, bx                  ; bx = 0
    add     bl, [a]
    add     bl, [b]
    idiv    bx

    add     [z], ax

    xor     ax, ax                  ; clean ax
    mov     al, [b]                 ; ax = b
    mov     bx, 10                  ; bx = 10
    imul    bx                      ; ax = ax * bx
    
    xor     bx, bx                  ; ebx = 0
    add     bl, [c]
    add     bx, [d]
    idiv    bx

    add     [z], ax

    ; print
    mov             rdi, output_format
    movsx           esi, word [z]
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit


 