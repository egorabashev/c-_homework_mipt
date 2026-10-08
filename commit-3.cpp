#include <chrono>
#include <functional>
#include <iostream>
#include <string>
using namespace std;

int add(int a, int b) { return a + b; }

template <typename R, typename... Args>
function<R(Args...)> logger(function<R(Args...)> func, string name) {
    return [func, name](Args... args) {
        cout << "call " << name << "\n";
        R result = func(args...);
        cout << name << " returned " << result << "\n";
        return result;
    };
}

template <typename R, typename... Args>
function<R(Args...)> timer(function<R(Args...)> func) {
    return [func](Args... args) {
        auto start = chrono::steady_clock::now();
        R result = func(args...);
        auto end = chrono::steady_clock::now();
        cout << "time " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
        return result;
    };
}

using Strategy = function<double(double)>;

Strategy noDiscount() {
    return [](double price) { return price; };
}

Strategy percentDiscount(double percent) {
    return [percent](double price) { return price * (1 - percent / 100); };
}

Strategy fixedDiscount(double amount) {
    return [amount](double price) { return price > amount ? price - amount : 0; };
}

double checkout(double price, const Strategy& strategy) {
    return strategy(price);
}

int main() {
    function<int(int, int)> f = add;
    auto decorated = timer(logger(f, "add"));
    decorated(2, 3);

    cout << checkout(1000, noDiscount()) << "\n";
    cout << checkout(1000, percentDiscount(10)) << "\n";
    cout << checkout(1000, percentDiscount(25)) << "\n";
    cout << checkout(100, fixedDiscount(300)) << "\n";
    cout << checkout(1000, [](double p) { return p / 2; }) << "\n";
}