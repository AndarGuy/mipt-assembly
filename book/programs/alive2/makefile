# makefile for alive2.asm

.SILENT:

alive2: alive2.o
	gcc -o alive2 alive2.o -no-pie
alive2.o: alive2.asm
	nasm -f macho64 -g -F dwarf alive2.asm -l alive2.lst