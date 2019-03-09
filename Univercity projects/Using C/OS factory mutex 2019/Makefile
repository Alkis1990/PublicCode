OBJS	= structure.o main.o queue.o
SOURCE	= structure.c main.c queue.c
HEADER	= timespan.h structure.h queue.h
OUT	= a.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

structure.o: structure.c
	$(CC) $(FLAGS) structure.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 

queue.o: queue.c
	$(CC) $(FLAGS) queue.c 


clean:
	rm -f $(OBJS) $(OUT)