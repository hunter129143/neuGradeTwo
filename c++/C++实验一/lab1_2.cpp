#include <iostream>
using namespace std;

int Max1(int a, int b);
int Max1(int a, int b, int c);
double Max1(double a, double b);
double Max1(double a, double b, double c);

int main() {
    int max1 = Max1(1, 2);
    int max2 = Max1(1, 2, 3);
    double max3 = Max1(1.0, 2.0);
    double max4 = Max1(1.0, 2.0, 3.0);
    cout << "the max number of (1,2) is: " << max1 << endl
        << "the max number of (1,2,3) is: " << max2 << endl
        << "the max number of (1.0,2.0) is: " << max3 << endl
        << "the max number of (1.0,2.0,3.0) is: " << max4 << endl;
    return 0;
}

int Max1(int a, int b) {
    int max = a;
    if (max < b) {
        max = b;
    }
    return max;
}

int Max1(int a, int b, int c) {
    int max = a;
    if (max < b) {
        max = b;
    }
    if (max < c) {
        max = c;
    }
    return max;
}

double Max1(double a, double b) {
    double max = a;
    if (max < b) {
        max = b;
    }
    return max;
}

double Max1(double a, double b, double c) {
    double max = a;
    if (max < b) {
        max = b;
    }
    if (max < c) {
        max = c;
    }
    return max;
}