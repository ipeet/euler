# Generic-ish Makefile which just builds each source file into its own
# binary.  All .c files must have mains!

CC=gcc
CFLAGS=-O2 -g3
INCLUDES=-I/usr/include/ipmath
LIBS=-lm -lipmath
.SECONDEXPANSION: 


CC_SRCS=$(wildcard *.c)
CC_BINARIES=$(patsubst %.c,%,$(CC_SRCS))
BINARIES+=$(CC_BINARIES)

.phony=all
all: $(BINARIES)

$(CC_BINARIES): $(patsubst %,%.c,$$(@))
	$(CC) $(CFLAGS) $(INCLUDES) $(patsubst %,%.c,$(@)) $(LIBS) -o $(@)

.phony=clean
clean: ; rm -f $(BINARIES)

.phony=debug_vars

debug_vars:
	@echo CC_SRCS: $(CC_SRCS)
	@echo CC_BINARIES: $(CC_BINARIES)
	@echo BINARIES: $(BINARIES)



