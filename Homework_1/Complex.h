#pragma one
#include <iostream>

class Complex {
	int a;
	int b;
	friend Complex operator*(const int num_val, const Complex val); //for num_val*(a+bi) 
public:
	Complex(int a_, int b_); //constructor
	Complex() = default;//defoulte constructor

	Complex operator+(const Complex val);//for +
	Complex operator-(const Complex val);//for -
	Complex operator*(const int num_val);//for (a+bi)*num_val

	double absolute_val();//for getting absolute value
	void print_complex(); //for printing complex number

};

void SortForComplex(Complex array[], const int size);//for sorting complex numbers

