CC = gcc

CFLAGS = -Wall -g

SRCS = binary_tree.c linked_list.c hashmap.c  \
	heapsort.c quick_sort.c merger_sort.c selection_sort.c insertion_sort.c

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
