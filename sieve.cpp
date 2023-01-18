#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

std::mutex mtx;

const long long upperBound = 100000000 + 1;
const long long sqrtOfUpperBound = 10000 + 1;

void checkNonPrimes(long long start, vector <bool> &primeList);
int getNextNumber(vector <bool> &ticketArray);
void findAllPrimes(vector <bool> &primeList, vector <bool> &ticketArray, int start);

int main() {
    // start timer
    auto start = high_resolution_clock::now();
    cout << "Program Started" << endl;

    vector <bool> primeList(upperBound, true);
    //false if not yet used (or dont need to use)
    //true if used
    vector <bool> ticketArray(sqrtOfUpperBound, false);

    primeList[0] = false;
    primeList[1] = false;
    ticketArray[0] = true;
    ticketArray[1] = true;    

    thread t1(findAllPrimes, ref(primeList), ref(ticketArray), 2);
    thread t2(findAllPrimes, ref(primeList), ref(ticketArray), 3);
    thread t3(findAllPrimes, ref(primeList), ref(ticketArray), 5);
    thread t4(findAllPrimes, ref(primeList), ref(ticketArray), 7);
    thread t5(findAllPrimes, ref(primeList), ref(ticketArray), 11);
    thread t6(findAllPrimes, ref(primeList), ref(ticketArray), 13);
    thread t7(findAllPrimes, ref(primeList), ref(ticketArray), 17);
    thread t8(findAllPrimes, ref(primeList), ref(ticketArray), 19);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    
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
    cout << "Microseconds: " << duration.count() << " microseconds" << endl;
    cout << "Seconds: " << duration.count() / 1000000.0 << " seconds" << endl;

    return 0;

}

void checkNonPrimes(long long start, vector <bool> &primeList) {
    for (long long i = start * start; i < upperBound; i += start) {
        if (primeList[i] == false) {
            continue;
        }
        mtx.lock();
        primeList[i] = false;
        mtx.unlock();
    }
}

int getNextNumber(vector <bool> &ticketArray) {
    for (int i = 2; i < sqrtOfUpperBound; i++) {
        if (ticketArray[i] == false) {
            mtx.lock();
            if (ticketArray[i] == true) {
                mtx.unlock();
                continue;
            }
            ticketArray[i] = true;
            mtx.unlock();
            return i;
        }
    }
    return -1;
}

void findAllPrimes(vector <bool> &primeList, vector <bool> &ticketArray, int start) {
    int nextNumber = start;
    while (nextNumber != -1) {
        checkNonPrimes(nextNumber, primeList);
        nextNumber = getNextNumber(ticketArray);
    }
}
    

    
