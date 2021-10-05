#include "Matrix.h"
#include <iostream>
using namespace std;

int main() {
	try {
		matrix<int> m(2, 2);
		matrix<int> m2(2, 2);
		cin >> m;
		cin >> m2;
		cout << m2 << endl;
		m2 += m;
		cout << m << endl << m2 << endl;
		auto m3 = m + m2;
		cout << m3 << endl;
	}
	catch (const std::exception& e) {
		cerr << e.what() << endl;
	}
	return 0;
}
