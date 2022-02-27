
; --- .data DATATYPES ---
; Type  Length   Name
; db    8 bits   Byte
; dw    16 bits  Word
; dd    32 bits  Double word
; dq    64 bits  Quadword

section .data
    pi  equ     3.1416  ; constant

; --- .bss DATATYPES ---
; Type  Length   Name
; resb  8 bits   Byte
; resw  16 bits  Word
; resd  32 bits  Double word
; resq  64 bits  Quadword

section .bss ; acronym of Block Started by Symbol
    array resd  20      ; an array of 20 double words

section .text
    global _main

_main:
    mov destination, source ; makes the copy of data from the source to the destination
        ; possible formats
        mov register, immediate value
        mov register, memory
        mov memory, register
        !illegal: mov memory, memory
    
    syscall ; calls functionality provided by the operating system
        ; different systems
        macho64: (0x2000000 + unix syscall #)
        linux: freebsd syscall ; syscalls/freebsd.md : https://sigsegv.pl/osx-bsd-syscalls/
        windows: ;
