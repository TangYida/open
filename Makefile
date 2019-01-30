FLAGS=-std=c++0x
CC=g++

all: open

open: open.o
	$(CC) -o open open.o $(FLAGS)

open.o: nlohmann/json.hpp Editor.hpp
	$(CC) -c open.cpp $(FLAGS)

run:
	./open

.PHONY:clean
clean:
	rm -f open.o
