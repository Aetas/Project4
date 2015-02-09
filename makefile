#sheblamo
CC=g++
CFLAGS=-Wall -std=c++0x
# 
WKDIR=($(HOME)/programs/csci-2270/project2/)

all: program

program: Assignment2.cpp
	$(CC) $(CFLAGS) Assignment2.cpp -o Assignment2.o

clean:
	rm *o Assignment2

