; nasm -fmacho64 io.asm && gcc io.o && ./a.out

global _main

section .text

_main:
    mov     rax, 0x2000003  ; SYS_read setup (SYS_write at 3 bits offset from 0x02000000)
    mov     rdi, 2          ; SYS_read use STDIN
    mov     rsi, character  ; SYS_read store the byte at `character`
    mov     rdx, 1          ; SYS_read read up to 1 byte only
    syscall

    mov     rax, 0x2000004  ; SYS_write setup (SYS_write at 4 bits offset from 0x02000000)
    mov     rdi, 1          ; SYS_write use STDOUT
    mov     rsi, character  ; SYS_write argument
    mov     rdx, 1          ; SYS_write argument size (bytes)
    syscall

    mov     rax, 0x2000001 ; exit
    mov     rdi, 0
    syscall


section .data

character: db 1