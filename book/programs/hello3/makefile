# makefile for hello3.asm

.SILENT:

hello3: hello3.o
	gcc -o hello3 hello3.o -no-pie
hello3.o: hello3.asm
	nasm -f macho64 -g -F dwarf hello3.asm -l hello3.lst