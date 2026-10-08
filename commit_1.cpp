#include <iostream>
#include <functional>
using namespace std;
int square(int x) { return x * x; }
function<int(int)> logger(function<int(int)> func) {
    return [func](int x) {
        cout << "call " << x << "\n";
        func(x);
    };
}
double checkout(double price, string type) {
    if (type == "percent") return price * 0.9;
    else if (type == "fixed") return price - 300;
    return price;
}
int main() {
    auto f = logger(square);
    cout << f(5) << "\n";
    cout << checkout(1000, "percent") << "\n";
    cout << checkout(100, "fixed") << "\n";
}