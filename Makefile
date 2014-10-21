
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = 
CFLAGS      = $(INCLUDE_DIR)
CCFLAGS     = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    =
LIB_LIST    = -lm
LIBS        = $(LIB_PATH) $(LIB_LIST)

EXEC        = hashing
objects     = WordCounter.o HashTable.o porter.o main.o

default: $(EXEC)

$(EXEC): $(objects)
	g++ -g -o $(EXEC) $(objects)

WordCounter.o : WordCounter.cc WordCounter.h
	g++ -c WordCounter.cc -o WordCounter.o

porter.o : porter.cc porter.h
	g++ -c porter.cc -o porter.o -w

HashTable.o : HashTable.cc HashTable.h WordCounter.h
	g++ -c HashTable.cc -o HashTable.o

main.o : main.cc HashTable.h porter.h
	g++ -c main.cc -o main.o

clean :
	rm *.o
	rm $(EXEC)



