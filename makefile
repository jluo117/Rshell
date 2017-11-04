CFLAGS=-Wall -Werror -ansi -pedantic
EXEC=rshell
FINEXEC=bin/rshell
all:rshell
	mkdir -p bin
	mv $(EXEC) $(FINEXEC)

rshell:
	g++ $(CFLAGS) src/*.cpp -o $(EXEC)

clean:
	rm -r -f bin
