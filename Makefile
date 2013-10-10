all: prog3

prog3: prog3.o node0.o node1.o node2.o node3.o comfun.o
	gcc prog3.o node0.o node1.o node2.o node3.o comfun.o -o prog3
	
node0.o: node0.c comfun.h
	gcc -c node0.c
	
node1.o: node1.c comfun.h
	gcc -c node1.c
	
node2.o: node2.c comfun.h
	gcc -c node2.c

node3.o: node3.c comfun.h
	gcc -c node3.c

comfun.o: comfun.c comfun.h
	gcc -c comfun.c
	
clean:
	rm -f *.o prog3