CC = g++
CFLAGS = -Wextra -lX11
SOURCES = $(wildcard *.cpp) $(wildcard buttons/*.cpp) $(wildcard events/*.cpp) $(wildcard windows/*.cpp) examples/main.cpp
TARGET = examples/example

build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
run:
	./$(TARGET)

