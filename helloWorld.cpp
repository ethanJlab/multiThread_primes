#include <iostream>
#include <string>
using namespace std;

class weedClass {
    public:
    int weedNum;
    string weedName;
    void weedFunc() {
        cout << "I am a " << weedName << " and I have " << weedNum << " leaves." << endl;
    }
    void print420() {
        cout << "420" << endl;
    }
    void print69();
    void printNum(int num = 1);

    weedClass(int x, string y = "weed") {
        weedNum = x;
        weedName = y;
    }
    void printWeed() {
        cout << "I am a " << weedName << " and I have " << weedNum << " leaves." << endl;
    }
};

void weedClass::print69() {
    cout << "69" << endl;
} 

void weedClass::printNum(int num) {
    cout << num << endl;
}

int main() {
    int age;
    cout << "Enter your age: ";
    cin >> age;

    try {
        if (age >= 18) {
            cout << "Access granted - you are old enough." << endl;
        } else {
            throw (age);
        }
    } catch (...) {
        cout << "Access denied - You must be at least 18 years old." << endl;
        cout << "Age is: " << 5 << endl;
    }
}