; alive.asm

section .data
    message1            db      "Hello, World!", 10, 0          ; string
    message1_length     equ     $ - message1 - 1                ; measure the length, minus the 0
    message2            db      "Alive and Kicking!", 10, 0     ; string
    message2_length     equ     $ - message2 - 1                ; measure the length, minus the 0
    radius              dq      357                             ; no string, not displayable?
    pi                  dq      3.14                            ; no string, not displayable?

section .bss

section .text
    global _main

_main:
    mov     rax, 0x2000000 + 4      ; 4 = write
    mov     rdi, 1                  ; 1 = stdout
    mov     rsi, message1           ; string to display
    mov     rdx, message1_length    ; length of the string
    syscall                         ; display the string

    mov     rax, 0x2000000 + 4      ; 4 = write
    mov     rdi, 1                  ; 1 = stdout
    mov     rsi, message2           ; string to display
    mov     rdx, message2_length    ; length of the string
    syscall                         ; display the string

    mov     rax, 0x2000000 + 1      ; 1 = exit
    mov     rdi, 0                  ; 0 = success exit code
    syscall                         ; quit

    

