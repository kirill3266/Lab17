#include "Matrix.h"
#include <iostream>

using namespace std;

int main() {
    try {
        matrix<int> m(2, 2);
        cin >> m;
        cout << m;
        findBack(m);
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
    }
    return 0;
}
