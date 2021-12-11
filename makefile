CC = gcc

test:
	gcc test.c ask2_help.c -o askisi2

.PHONY: clean
clean:
	rm askisi2