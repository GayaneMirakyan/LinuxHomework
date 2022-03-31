all: ipc

ipc: PipeComunication.o
	g++ PipeComunication.o -o ipc

PipeComunication.o: PipeComunication.cpp
	g++ -c PipeComunication.cpp

clean: 
	rm *.o ipc

