# makefile for 3.asm

.SILENT:

3: 3.o
	gcc -o 3 3.o
3.o: 3.asm
	nasm -f macho64 -g -F dwarf 3.asm -l 3.lst