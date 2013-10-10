all: prog3

prog3: prog3.o node0.o node1.o node2.0 node3.o comfun.o
	gcc prog3.o node0.o node1.o node2.o node3.o comfun.o -o prog3
	
node0.o: node0.c comfun.h
	gcc -c node0.c
	
node0.o: node1.c comfun.h
	gcc -c node1.c
	
node0.o: node2.c comfun.h
	gcc -c node2.c

node0.o: node3.c comfun.h
	gcc -c node3.c

node0.o: comfun.c comfun.h
	gcc -c comfun.c
	
clean:
	rm *.o prog3