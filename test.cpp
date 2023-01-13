#include <iostream>
#include <thread>
#include <mutex>
#include <map>
using namespace std;
long long total = 10;

void add2() {
    total += 2;
}

int main() {
    long long sum = 0;

    cout << "Before: " << total << endl;
    thread t1(add2);
    thread t2(add2);
    t1.join();
    t2.join();

    cout << "After: " << total << endl;

    for (long long i = 0; i < 100000000; i++) {
        sum += i;
        cout << sum << endl;
    }
    // find all the multiples of 2 from 1 to 100000000 and subtract them from the sum

    cout << "Sum: " << sum << endl;

    for (long long i = 0; i < 100000000; i++) {
        if (i == 0 || i == 2) {
            continue;
        }
        if (i % 2 == 0) {
            sum = sum - i;
            
        }
    }

    cout << "Sum: " << sum << endl;

    return 0;
}