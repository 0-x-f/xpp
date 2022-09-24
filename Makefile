CC = g++

CFLAGS = -Wextra -Wall -lX11
LFLAGS = $(CFLAGS) -fPIC

SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
LIB_SOURCES = $(wildcard *.cpp) $(filter-out $(wildcard examples/*.cpp), $(wildcard */*.cpp))

OBJECTS = $(addprefix obj/, $(notdir $(SOURCES:.cpp=.o)))
LIB_OBJECTS = $(addprefix obj/, $(notdir $(LIB_SOURCES:.cpp=.o)))

TARGET = examples/example
LIB = libxpp.so

vpath %.cpp $(dir $(LIB_SOURCES))

lib: $(LIB_OBJECTS)
	$(CC) $(LFLAGS) -shared -o $(LIB) $(LIB_OBJECTS)
build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)
obj/%.o: %.cpp
	$(CC) $(LFLAGS) -c $< -o $@
run:
	./$(TARGET)
clean:
	rm -rf $(OBJECTS) $(TARGET)
