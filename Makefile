.SUFFIXES:
TARGETS=hp2sp sp2hp float2hex norm

CC=gcc
LD=gcc
LFLAGS=-lm
CFLAGS=-g -Wfatal-errors -O1 -Wall
DEPS:=$(wildcard *.h) Makefile

#########

all: $(TARGETS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o
	$(LD) -o $@ $^ $(LFLAGS)

clean:
	rm -rf *.o $(TARGETS)
