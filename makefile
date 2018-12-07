all: program6
program6: bst.o program6.o
	gcc bst.o program6.o -o program6
program6.o: program6.c
	gcc -c program6.c -o program6.o
bst.o: bst.c
	gcc -c bst.c -o bst.o
run: program6    
	./program6
checkmem: program6
	valgrind ./program6	
clean:
	rm -rf program6 bst *.o