CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic -std=c++11
EXEC = test.out
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c -g $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
