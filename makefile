r4850 : r4850.o 
	cc -o r4850 r4850.o -lrt

r4850.o : r4850.c
	cc -c r4850.c

clean :
	rm r4850 r4850.o 
