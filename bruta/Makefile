all: item.o mochila.o bruta.o
	gcc item.o mochila.o bruta.o -o bruta
item.o:
	gcc item.c -Wall -std=c99 -c
mochila.o:
	gcc mochila.c -Wall -std=c99 -c
bruta.o:
	gcc bruta.c -Wall -std=c99 -c
run:
	./bruta
clean:
	rm mochila.o bruta.o bruta