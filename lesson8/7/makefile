# makefile for 7.asm

.SILENT:

7: 7.o
	gcc -o 7 7.o
7.o: 7.asm
	nasm -f macho64 -g -F dwarf 7.asm -l 7.lst