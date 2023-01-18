#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

std::mutex mtx;

const long long upperBound = 100 + 1;
const long long sqrtOfUpperBound = 10 + 1;

void checkNonPrimes(long long start, vector <bool> &primeList);

int main() {
    // start timer
    auto start = high_resolution_clock::now();

    vector <bool> primeList(upperBound, true);

    primeList[0] = false;
    primeList[1] = false;

    for (long long i = 2; i < sqrtOfUpperBound; i++) {
        if (primeList[i] == true) {
            checkNonPrimes(i, primeList);
        }
    }

    
    long long sum = 0;
    long long numPrimes = 0;

    for (long long i = 0; i < upperBound; i++) {
        if (primeList[i] == true) {
            sum += i;
            numPrimes++;
        }
    }

    cout << "Sum of all primes: " << sum << endl;
    cout << "Number of primes: " << numPrimes << endl;

    // end timer
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Microseconds: " << duration.count() << " microseconds" << endl;
    cout << "Seconds: " << duration.count() / 1000000.0 << " seconds" << endl;


    return 0;

}

void checkNonPrimes(long long start, vector <bool> &primeList) {
    for (long long i = start * start; i < upperBound; i += start) {
        mtx.lock();
        primeList[i] = false;
        mtx.unlock();
    }
}

// to commemorate when github copilot went schitzo on me LMAO
/*
I'm not sure if this is the best way to do it, but it works. I'm not sure if I should be using a mutex or not, but I'm using it anyway. I'm also not sure if I should be using a vector or not, but I'm using it anyway. I'm also not sure if I should be using a thread or not, but I'm using it anyway. I'm also not sure if I should be using a for loop or not, but I'm using it anyway. I'm also not sure if I should be using a if statement or not, but I'm using it anyway. I'm also not sure if I should be using a cout or not, but I'm using it anyway. I'm also not sure if I should be using a function or not, but I'm using it anyway. I'm also not sure if I should be using a main or not, but I'm using it anyway. I'm also not sure if I should be using a namespace or not, but I'm using it anyway. I'm also not sure if I should be using a using or not, but I'm using it anyway. I'm also not sure if I should be using a std or not, but I'm using it anyway. I'm also not sure if I should be using a chrono or not, but I'm using it anyway. I'm also not sure if I should be using a high_resolution_clock or not, but I'm using it anyway. I'm also not sure if I should be using a duration or not, but I'm using it anyway. I'm also not sure if I should be using a duration_cast or not, but I'm using it anyway. I'm also not sure if I should be using a microseconds or not, but I'm using it anyway. I'm also not sure if I should be using a count or not, but I'm using it anyway. I'm also not sure if I should be using a endl or not, but I'm using it anyway. I'm also not sure if I should be using a return or not, but I'm using it anyway. I'm also not sure if I should be using a void or not, but I'm using it anyway. I'm also not sure if I should be using a long long or not, but I'm using it anyway. I'm also not sure if I should be using a const or not
*/