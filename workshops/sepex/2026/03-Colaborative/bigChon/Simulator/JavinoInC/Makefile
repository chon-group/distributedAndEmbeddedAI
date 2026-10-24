
SRC = javino.c
OBJ = $(SRC:.c=.o)

ALL_CFLAGS = -Wall -Wextra -Iinclude -O2 $(CFLAGS)

CC = gcc
LD = gcc
AR = ar

VPATH = src

%.o: %.c 
	$(CC) $(ALL_CFLAGS) -c $< -o $@

.PHONY: all clean

all: $(OBJ)
	mkdir -p lib
	$(AR) cru lib/libjavino.a $(OBJ)

all-dbg:
	make CFLAGS="-D__EXTRA_DEBUG_MESSAGES__ -g" all

tests:
		

clean:
	rm -f lib/libjavino.a
	rm -f *.o

