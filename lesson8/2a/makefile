# makefile for 2.asm

.SILENT:

2: 2.o
	gcc -o 2 2.o
2.o: 2.asm
	nasm -f macho64 -g -F dwarf 2.asm -l 2.lst