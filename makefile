CC = gcc
CFLAGS = -Wall

chexdump: main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm chexdump
