compile:
	gcc main.c hashmap.c chain.c

test:
	gcc main.c hashmap.c chain.c -g
	valgrind ./a.out < 1.txt 

start: compile
	./a.out < 2.txt