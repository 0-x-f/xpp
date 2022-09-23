CC = g++
CFLAGS = -Wextra -lX11
# SOURCES = $(wildcard *.cpp) $(wildcard buttons/*.cpp) $(wildcard events/*.cpp) $(wildcard windows/*.cpp) examples/main.cpp
SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
TARGET = examples/example

build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
run:
	./$(TARGET)

