# makefile for 5.asm

.SILENT:

5: 5.o
	gcc -o 5 5.o
5.o: 5.asm
	nasm -f macho64 -g -F dwarf 5.asm -l 5.lst