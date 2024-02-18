
ALL_CFLAGS = $(CFLAGS) -Wall -Wextra -I../include

ALL_LDFLAGS = $(LDFLAGS) ../lib/libjavino.a

BIN = javino_recv javino_send

%.o: %.c
	$(CC) $(ALL_CFLAGS) -c $< -o $@

.PHONY: all clean

all: ../lib/libjavino.a $(BIN)

../lib/libjavino.a: 
	make -C../ clean all

javino_recv: javino_recv.o
	$(CC) $< $(ALL_LDFLAGS) -o $@

javino_send: javino_send.o
	$(CC) $< $(ALL_LDFLAGS) -o $@

clean:
	make -C../ clean
	rm -f *.o $(BIN)
