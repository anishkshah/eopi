CC = gcc

CFLAGS = -Wall -g

SRCS = binary_tree.c linked_list.c hashmap.c heapsort.c

OBJS = $(SRCS:.c=.o)

MAIN = test

.PHONY: depend clean

all:    $(MAIN)
		@echo  All data structures have been compiled

$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
		makedepend $^