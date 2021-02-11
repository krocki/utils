.SUFFIXES:
TARGETS=systime hp2sp sp2hp float2hex norm hex2bin epoch2date

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
