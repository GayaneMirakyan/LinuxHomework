all: output

output: main.o Complex.o
	g++ main.o Complex.o -o output

main.o: main.cpp Complex.h
	g++ -c main.cpp

Complex.o: Complex.cpp Complex.h
	g++ -c Complex.cpp

clean: 
	rm *.o output



