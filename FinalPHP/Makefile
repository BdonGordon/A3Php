CC = gcc 
CFLAGS = -Wall -g

all: listio

listio: listio.o listHelper.o a3.o
	ar rc liblistio.a listio.o listHelper.o
	$(CC) $(CFLAGS) a3.o liblistio.a -o a3

listio.o: listio.h listio.c
	$(CC) $(CFLAGS) -c listio.c

listHelper.o: listio.h listHelper.c
	$(CC) $(CFLAGS) -c listHelper.c

a3.o: a3.c
	$(CC) $(CFLAGS) -c a3.c

clean:	
	@ rm -f *.o liblistio.a 
	rm a3
