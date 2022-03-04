# makefile for 1.asm

.SILENT:

1: 1.o
	gcc -o 1 1.o
1.o: 1.asm
	nasm -f macho64 -g -F dwarf 1.asm -l 1.lst