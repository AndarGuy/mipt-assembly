# makefile for hello.asm

.SILENT:

hello: hello.o
	gcc -o hello hello.o -no-pie
hello.o: hello.asm
	nasm -f macho64 -g -F dwarf hello.asm -l hello.lst