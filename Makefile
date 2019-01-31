FLAGS=-std=c++0x
CC=g++

all: open new

#open
open: open.o
	$(CC) -o open open.o $(FLAGS)

open.o: nlohmann/json.hpp Editor.hpp
	$(CC) -c open.cpp $(FLAGS)

#new	
new: new.o	
	$(CC) -o new new.o $(FLAGS)

new.o: nlohmann/json.hpp Editor.hpp
	$(CC) -c new.cpp $(FLAGS)

run:
	echo "Hello"

.PHONY:clean
clean:
	rm -f open.o
