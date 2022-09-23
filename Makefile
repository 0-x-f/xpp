CC = g++
CFLAGS = -Wextra -lX11
SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS = obj/$(SOURCES:.cpp=.o)
TARGET = examples/example

all: build

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@
run:
	./$(TARGET)
clean: $(OBJECTS)
	rm -rf $@


