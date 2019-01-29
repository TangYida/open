FLAGS=-std=c++17
CC=g++

all: open

open: open.o
	$(CC) -o open open.o $(FLAGS)

open.o: nlohmann/json.hpp

run:
	./open

.PHONY:clean
clean:
	rm -f open.o
