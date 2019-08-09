CC	= gcc
CFLAGS	= -g -Wall
PROGS	= unique

.PHONY: all
all:	$(PROGS)

clean:
	$(RM) $(PROGS) *.o core
.PHONY: clean

unique:	unique.o table.o
	$(CC) -o $@ $(CFLAGS) unique.o table.o
.PHONY: unique

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@