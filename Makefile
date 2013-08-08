CC=gcc
CFLAGS=-O2 -std=c99
EXTRA_FLAGS=
CFLAGS+=$(EXTRA_FLAGS)

power: power.c
	$(CC) -o power power.c $(CFLAGS)

power-montgomery: power.c
	$(CC) -o power-montgomery power.c $(CFLAGS) -DPOWER=montgomery_ladder

ALL=power power-montgomery

all: $(ALL)

cortex-a15:
	$(MAKE) all EXTRA_FLAGS=-mcpu=cortex-a15

clean:
	rm $(ALL)
