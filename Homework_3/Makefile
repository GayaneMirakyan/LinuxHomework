all: myShell

myShell: myShell.o
	g++ myShell.o -o myShell

myShell.o: myShell.cpp
	g++ -c myShell.cpp

clean: 
	rm *.o myShell
