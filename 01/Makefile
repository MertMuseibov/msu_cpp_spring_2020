CC=g++
CFLAGS = --std=c++14
compile: main.cpp
        $(CC) main.cpp -o main $(CFLAGS)

main.o: compile
        g++ -c main.cpp
test: main.o
        g++ -o main.o
