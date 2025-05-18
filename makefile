CC = g++
CFLAGS = -g -Wall -std=c++11

play: person.h role.h main.cc
	$(CC) $(CFLAGS) main.cc -o play
	