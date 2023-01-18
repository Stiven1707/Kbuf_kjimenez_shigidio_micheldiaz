
debug: kbuf.c main.c
	gcc -g -o kbuf main.c kbuf.c

all: kbuf.o main.o
	gcc -g -o kbuf main.o kbuf.o

kbuf.o: kbuf.c
	gcc -c -o kbuf.o kbuf.c

main.o: main.c
	gcc -c -o main.o main.c

clean:
	rm -f *.o kbuf
	