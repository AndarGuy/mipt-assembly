; hello2.asm

section .data
  message db      "Hello, World!", 0x0
  NL      db      0xA               ; ASCII code for new line

section .bss

section .text
  global _main

_main:
    mov       rax, 0x2000000 + 4    ; 4 = write
    mov       rdi, 1                ; 1 = to stdout
    mov       rsi, message          ; string to display in rsi
    mov       rdx, 13               ; length of the string, without 0
    syscall                         ; display the string

    mov       rax, 0x2000000 + 4    ; 4 = write
    mov       rdi, 1                ; 1 = to stdout
    mov       rsi, NL               ; display new line
    mov       rdx, 1                ; length of the string
    syscall                         ; display the string

    mov       rax, 0x2000000 + 1    ; 1 = exit
    mov       rdi, 0                ; 0 = success exit code
    syscall                         ; quit
