#include <iostream>
#include <string>
#include <thread>
using namespace std;

int main() {
    int arr[100];
    int* ptr = arr;
    int sum = 0;

    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    //print the array
    for (int i = 0; i < 100; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    thread t2([](int arr[] ) {
        for (int i = 0; i < 100; i+=2) {
            if (arr[i] = 0 || arr[i] == 2) {
                continue;
            }
            if (arr[i] % 2 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t3([](int arr[] ) {
        for (int i = 0; i < 100; i+=3) {
            if (arr[i] = 0 ) {
                continue;
            }
            if (arr[i] % 3 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t4 ([](int arr[] ) {
        for (int i = 0; i < 100; i+=4) {
            if (arr[i] = 0) {
                continue;
            }
            if (arr[i] % 4 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t5 ([](int arr[] ) {
        for (int i = 0; i < 100; i+=5) {
            if (arr[i] = 0) {
                continue;
            }
            if (arr[i] % 5 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t6 ([](int arr[] ) {
        for (int i = 0; i < 100; i+=6) {
            if (arr[i] = 0) {
                continue;
            }
            if (arr[i] % 6 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t7 ([](int arr[] ) {
        for (int i = 0; i < 100; i+=7) {
            if (arr[i] = 0) {
                continue;
            }
            if (arr[i] % 7 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t8 ([](int arr[] ) {
        for (int i = 0; i < 100; i+=8) {
            if (arr[i] = 0) {
                continue;
            }
            if (arr[i] % 8 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t9 ([](int arr[] ) {
        for (int i = 0; i < 100; i+=9) {
            if (arr[i] = 0) {
                continue;
            }
            if (arr[i] % 9 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    thread t10 ([](int arr[] ) {
        for (int i = 0; i < 100; i+=10) {
            if (arr[i] = 0) {
                continue;
            }
            if (arr[i] % 10 == 0) {
                arr[i] = 0;
            }
        }        
    }, arr);

    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    for (int i = 0; i < 100; i++) {
        if (arr[i] != 0) {
            sum += arr[i];
        }
    }

    //print the array
    cout << "The array is: " << endl;
    for (int i = 0; i < 100; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
    cout << sum << endl;
}