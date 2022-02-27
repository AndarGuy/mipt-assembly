# makefile for move.asm

.SILENT:

move: move.o
	gcc -o move move.o
move.o: move.asm
	nasm -f macho64 -g -F dwarf move.asm -l move.lst