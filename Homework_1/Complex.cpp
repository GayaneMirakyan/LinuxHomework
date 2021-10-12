#include "Complex.h"
#include <cmath>

Complex::Complex(int a_, int b_) : a(a_), b(b_) {}
Complex Complex::operator+(const Complex val) {
	Complex ans;
	ans.a = a + val.a;
	ans.b = b + val.b;
	return ans;
}

Complex Complex::operator-(const Complex val) {
        Complex ans;
        ans.a = a - val.a;
        ans.b = b - val.b;
        return ans;
}


void Complex::print_complex(){
	if(b > 0 && a != 0)
		std::cout << a << " + " << b << "i" << std::endl;
	else if(b == 0)
		std::cout << a << std::endl;
	else if(a == 0)
		std::cout << b << "i" << std::endl;
	else
		std::cout << a << " - " << (-1) * b << "i" << std::endl;
}

Complex Complex::operator*(const int num_val){
	Complex ans;
	ans.a = a * num_val;
	ans.b = b * num_val;
	return ans;
}

Complex operator*(const int num_val, const Complex val){
	Complex ans;
	ans.a = val.a * num_val;
	ans.b = val.b * num_val;
	return ans;	
}

double Complex::absolute_val(){
	double ans = a * a + b * b;
	ans = sqrt(ans);
        return ans;
}

void SortForComplex(Complex array[], const int size){
	for(int i = 0; i < size - 1; i++) {
		for(int j = 0; j < size - i - 1; j++) {
			if(array[j].absolute_val() > array[j+1].absolute_val()) {
				Complex temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

