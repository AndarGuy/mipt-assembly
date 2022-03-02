; Реализовать присваивание b = a; (не более двух команд) при условии:
; char a; short b

global _main

default rel

extern _printf

section .data
x               db      2
a               db      7

output_format   db      "Результат %d, остаток %d", 0xA, 0x0

section .text

_main:
    push    rbp                     ; save stack

    xor     rax, rax                ; clean rax
    mov     al, byte [x]            ; al = x
    imul    ax                      ; ax = ax * ax
    mov     bx, 10                  ; bx = 10
    imul    bx                      ; ax = ax * bx
    add     ax, 5                   ; ax = ax + 5
    mov     bx, ax                  ; bx = ax
    neg     bx                      ; bx = -bx
    mov     ax, 0x1                 ; ax = 1
    xor     rcx, rcx                ; clean rcx
    mov     cl, byte [x]            ; cl = x
    imul    cx                      ; ax = ax * cx
    imul    cx                      ; ax = ax * cx
    imul    cx                      ; ax = ax * cx
    neg     ax                      ; ax = -ax
    add     bx, ax                  ; bx = bx + ax
    mov     ax, bx                  ; ax = bx
    xor     rbx, rbx                ; clean rbx
    mov     bl, byte [a]            ; bl = a
    idiv    bl                      ; ah = ax / bl, al = ax % bl

    ; print
    mov             rdi, output_format
    movsx           esi, al
    movsx           edx, ah
    mov             rax, 0          ; no floating point
    call            _printf         ; printf(“%d   %d\n”, x, *xp);
  
    pop	rbp                         ; restore stack
    
    mov       rax, 0x2000000 + 0x1  ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit


 