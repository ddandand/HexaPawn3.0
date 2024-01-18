#==================================================
# MACRO definitions
CC = g++

#==================================================
# All Targets
all: main
	./main
	make clean

#Executable main depends on the files main.o board.o
main: main.o board.o
	$(CC) -o main main.o board.o

#main.o depends on the source file main.cpp and the header file board.hpp
main.o: main.cpp 
	$(CC) -c main.cpp

#board.o depends on the source file board.cpp and the header file board.hpp
board.o: board.cpp 
	$(CC) -c board.cpp 

#clean depends on nothing and removes all files generated in compilation.
clean:
	rm *.o
	rm main

#test