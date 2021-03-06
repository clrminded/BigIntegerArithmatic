# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
CC = g++
 
# ****************************************************
# Targets needed to bring the executable up to date
main: main.o
	$(CC) -o main main.o
 
# The main.o target can be written more simply
 
main.o: main.cpp Node.h NoSuchElementException.h IllegalArgumentException.h DoublyLinkedList.h BigInteger.h
	$(CC) -c main.cpp

clean:
	rm -vf *.o *.exe *.obj *.pdb *.ilk