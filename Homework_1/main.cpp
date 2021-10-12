#include "Complex.h"

int main(){
	Complex a(5, 2);
	Complex b(1, 9);
	Complex d(3, 4);
	Complex e(0, 1);
	Complex f(1, 2);
	Complex g(2, 4);
	const int n = 6;
	Complex arr[n] = {a, b, d, e, f, g};
	std::cout << "Array before sorting." << std::endl;
	for(int i = 0; i < n; i++) {
                arr[i].print_complex();
        }
	SortForComplex(arr, n);
	std::cout << "Array after sorting." << std::endl;
	for(int i = 0; i < n; i++) {
		arr[i].print_complex();
	}

	return 0;
}
