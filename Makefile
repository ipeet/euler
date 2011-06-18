# Generic-ish Makefile which just builds each source file into its own
# binary.  All .c files must have mains!

CC=gcc
CFLAGS=-O2 -g3
INCLUDES=
LIBS=-lm
.SECONDEXPANSION: 
OBJDIR= obj

# Sources which should be compiled and linked with all problems
# (Needed or not, won't worry about that too much)
COMMON_SRCS= \
    calc_primes.c
COMMON_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(COMMON_SRCS))

# All the files containing main functions and logic for each problem
PROB_SRCS=$(wildcard p*.c)
PROB_OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(PROB_SRCS))

BINARIES=$(patsubst %.c,%,$(PROB_SRCS))

.phony=all
all: $(BINARIES)

# Object compilation logic
$(PROB_OBJS) $(COMMON_OBJS): $$(patsubst $(OBJDIR)/%.o,%.c,$$(@)) $(OBJDIR)
	$(CC) $(CFLAGS) $(INDLUDES) -c $< -o $@

$(OBJDIR): ; mkdir $@

$(BINARIES): $$(patsubst %,$(OBJDIR)/%.o,$$(@)) $(COMMON_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

.phony=clean
clean: 
	rm -f $(BINARIES)
	rm -f obj/*.o

.phony=debug_vars

debug_vars:
	@echo PROB_SRCS: $(PROB_SRCS)
	@echo BINARIES: $(BINARIES)



