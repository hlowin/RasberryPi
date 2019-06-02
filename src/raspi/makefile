make: main.o blink.o
		gcc -o main main.o blink.o
blink.o: main.o
		gcc -c main.c
blink.o: blink.c
		gcc -c blink.c
clean:
		rm -f main.o blink.o