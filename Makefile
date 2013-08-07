CC=gcc
CFLAGS=-O2 -std=c99

power: power.c
	$(CC) -o power power.c $(CFLAGS)

ALL=power

all: $(ALL)

.PHONY: clean
clean:
	rm *.o $(ALL)
