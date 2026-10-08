#include <functional>
#include <iostream>
using namespace std;

int square(int x) { return x * x; }

function<int(int)> logger(function<int(int)> func) {
    return [func](int x) {
        cout << "call " << x << "\n";
        int result = func(x);
        cout << "result " << result << "\n";
        return result;
    };
}

double noDiscount(double price) { return price; }
double tenPercent(double price) { return price * 0.9; }
double minus300(double price) { return price > 300 ? price - 300 : 0; }

double checkout(double price, function<double(double)> strategy) {
    return strategy(price);
}

int main() {
    auto f = logger(square);
    f(5);

    cout << checkout(1000, noDiscount) << "\n";
    cout << checkout(1000, tenPercent) << "\n";
    cout << checkout(100, minus300) << "\n";
}