# makefile for 4.asm

.SILENT:

4: 4.o
	gcc -o 4 4.o
4.o: 4.asm
	nasm -f macho64 -g -F dwarf 4.asm -l 4.lst