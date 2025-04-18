#include "MathUtils.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int multiply(int a, int b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0.0)
        throw invalid_argument("Divisor cannot be zero");
    return a / b;
}

void showResult() {
    cout << "MathUtils library loaded successfully!" << endl;
}
