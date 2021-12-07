all: output

output: main.o ParallelMatrix.o
	g++ main.o ParallelMatrix.o -o output -lpthread

main.o: main.cpp ParallelMatrix.h
	g++ -c main.cpp

ParallelMatrix.o: ParallelMatrix.cpp ParallelMatrix.h
	g++ -c ParallelMatrix.cpp

clean:
	rm *.o output

