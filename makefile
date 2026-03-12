$CC = gcc
$CFLAGS = -W

chexdump: main.c
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm chexdump
