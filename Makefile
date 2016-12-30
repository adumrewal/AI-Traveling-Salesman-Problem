all: tsp.o
	gcc -o tsp tsp.c -lm

tsp.o: tsp.c
	gcc -c tsp.c

clean:
	rm *.o tsp
