OBJS	= Chain.o mymalloc.o Bucket.o main.o MemoryChain.o Allocator.o findchain.o MemoryChainBucket.o
SOURCE	= Chain.cpp mymalloc.cpp Bucket.cpp main.cpp MemoryChain.cpp Allocator.cpp findchain.cpp MemoryChainBucket.cpp
HEADER	= AddressBucket.h Allocator.h findchain.h MemoryChainBucket.h AddressChain.h Chain.h mymalloc.h Bucket.h MemoryChain.h Tree.h
OUT	= project1
CC	= g++
FLAGS	= -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) 


Chain.o: Chain.cpp
	$(CC) $(FLAGS) Chain.cpp 

mymalloc.o: mymalloc.cpp
	$(CC) $(FLAGS) mymalloc.cpp 

Bucket.o: Bucket.cpp
	$(CC) $(FLAGS) Bucket.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

MemoryChain.o: MemoryChain.cpp
	$(CC) $(FLAGS) MemoryChain.cpp 

Allocator.o: Allocator.cpp
	$(CC) $(FLAGS) Allocator.cpp 

findchain.o: findchain.cpp
	$(CC) $(FLAGS) findchain.cpp 

MemoryChainBucket.o: MemoryChainBucket.cpp
	$(CC) $(FLAGS) MemoryChainBucket.cpp 

clean:
	rm -f $(OBJS) $(OUT)
