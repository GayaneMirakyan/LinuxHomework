all: my_copy

my_copy: copyfile.o
	g++ copyfile.o -o my_copy

copyfile.o: copyfile.cpp
	g++ -c copyfile.cpp

clean:
	rm *.o my_copy
