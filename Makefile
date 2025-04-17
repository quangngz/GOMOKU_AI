CFLAGS = 
all: 
	gcc -Wall functions.h  main.c -o final
clean: 
	rm -f final