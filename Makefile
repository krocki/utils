.SUFFIXES:
TARGETS=fp

CC=gcc
LD=gcc
CFLAGS=-g -Wfatal-errors -O1 -Wall
DEPS:=$(wildcard *.h) Makefile

#########

all: $(TARGETS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

fp: fp.o
	$(LD) -o $@ $^ $(LFLAGS)

clean:
	rm -rf *.o $(TARGETS)
