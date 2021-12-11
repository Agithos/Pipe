CC = gcc

test:
	gcc askisi2.c ask2_help.c -o askisi2

.PHONY: clean try1 try2
clean:
	rm askisi2
try1:
	./askisi2 infile.txt ijkl 010101
try2:
	./askisi2 t1 o 11