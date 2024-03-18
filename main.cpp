#include <iostream>
#include <climits>
using namespace std;

const int INITIAL_STEP = 1;
const int NUM_ITERATIONS = 3;

double f(double x, double y) {
    return -2 * x * x + 2 * x * y - 2 * y * y + 12 * x + 12 * y + 3;
}

pair<double, double> findMax(double x, double y, double delta, bool isX) {
    double fxy, maxVal = INT_MIN, minVal, count = NUM_ITERATIONS;
    if (isX)
        x -= delta;
    else
        y -= delta;

    while (count--) {
        fxy = f(x, y);

        if (fxy >= maxVal) {
            maxVal = fxy;
            if (isX)
                minVal = x;
            else
                minVal = y;
        }
        cout << "f(" << x << "," << y << ") = " << fxy << endl;
        if (isX)
            x += delta;
        else
            y += delta;
    }

    if (isX)
        return make_pair(minVal, y);
    else
        return make_pair(x, minVal);
}

pair<double, double> findNextPair(double x, double y, double delta) {
    pair<double, double> pair1 = findMax(x, y, delta, true);
    cout << "f_max(" << pair1.first << ", " << pair1.second << ") = " << f(pair1.first, pair1.second) << endl << endl << endl;

    pair<double, double> pair2 = findMax(pair1.first, y, delta, false);
    cout << "f_max(" << pair2.first << ", " << pair2.second << ") = " << f(pair2.first, pair2.second) << endl;

    return pair2;
}

pair<double, double> updateValues(double x, double y, double delta, int step) {
    cout << endl << "=============================================================================================" << endl;
    cout << "Step " << step << endl << endl;

    pair<double, double> nextPair = findNextPair(x, y, delta);

    return nextPair;
}

int main() {
    double x = 0, y = 0, delta = 0.5;
    int step = INITIAL_STEP;

    while (true) {
        pair<double, double> nextPair = updateValues(x, y, delta, step);

        if (f(x, y) >= f(nextPair.first, nextPair.second)) {
            delta /= 2;
            if (f(x, y) == f(nextPair.first, nextPair.second))
                return 0;
        } else {
            x = nextPair.first;
            y = nextPair.second;
        }

        step++;
    }
}
