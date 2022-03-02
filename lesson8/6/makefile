# makefile for 4.asm

.SILENT:

6: 6.o
	gcc -o 6 6.o
6.o: 6.asm
	nasm -f macho64 -g -F dwarf 6.asm -l 6.lst