CFLAGS=-Wall -g -Werror -ansi -pedantic -std=c++11
EXEC=rshell
FINEXEC=bin/rshell
all:rshell
	mkdir -p bin
	mv $(EXEC) $(FINEXEC)

rshell:
	g++ $(CFLAGS) src/*.cpp -o $(EXEC)

clean:
	rm -r -f bin
