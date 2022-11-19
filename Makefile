LIB_PATH=./src/impl
LIBS=${shell find ${LIB_PATH} -name '*.cpp'}

CC=g++
CFLAGS=-Wall -Wextra -pthread -std=c++11

build:
	$(CC) $(CFLAGS) ./src/main.cpp ${LIBS} -o tema1

clean:
	rm -rf tema1

all: build clean
	./test.sh
