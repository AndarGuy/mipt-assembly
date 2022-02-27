# makefile for alive.asm

.SILENT:

alive: alive.o
	gcc -o alive alive.o -no-pie
alive.o: alive.asm
	nasm -f macho64 -g -F dwarf alive.asm -l alive.lst