
ALL_CFLAGS = $(CFLAGS) -Wall -Wextra -I../include

ALL_LDFLAGS = $(LDFLAGS) ../lib/libjavino.a

SRC = javino_recv.c javino_send.c test01.c

BIN = $(SRC:.c=.bin)

CC = gcc
LD = gcc


%.bin: %.o
	$(LD) $< -o $@ $(ALL_LDFLAGS)

%.o: %.c
	$(CC) $(ALL_CFLAGS) -c $< -o $@

.PHONY: all clean

all: ../lib/libjavino.a $(BIN)

../lib/libjavino.a: 
	make -C../ debug

clean:
	make -C../ clean
	rm -f *.o $(BIN)
