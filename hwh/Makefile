compile:
	gcc main.c hashmap.c chain.c

test: compile
	valgrind ./a.out < in.txt 

start: compile
	./a.out < in.txt