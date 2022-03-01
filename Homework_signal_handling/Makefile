all: SignalHandling

SignalHandling: SignalHandling.o
	g++ SignalHandling.o -o SH

SignalHandling.o: SignalHandling.cpp
	g++ -c SignalHandling.cpp

clean:
	rm *.o SH
