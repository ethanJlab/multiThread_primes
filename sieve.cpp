#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <fstream>
using namespace std;
using namespace std::chrono;

std::mutex mtx;

const long long upperBound = 1000000 + 1;
const long long sqrtOfUpperBound = 1000 + 1;
long long sum = 2;
long long numPrimes = 1;

void checkNonPrimes(long long start, vector <bool> &primeList);
int getNextNumber(vector <bool> &ticketArray, int start, vector <bool> &primeList);
void findSomePrimes(vector <bool> &primeList, vector <bool> &ticketArray, int start);
void checkAllNonePrimes(long long start, vector <bool> &primeList);
void findAllPrimes(vector <bool> &primeList, vector <bool> &ticketArray, int start);
void addPrimes(vector <bool> &primeList, int start);

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

    thread t1(findSomePrimes, ref(primeList), ref(ticketArray), 3);
    thread t2(findSomePrimes, ref(primeList), ref(ticketArray), getNextNumber(ticketArray, 5, primeList));
    thread t3(findSomePrimes, ref(primeList), ref(ticketArray), getNextNumber(ticketArray, 7, primeList));
    thread t4(findSomePrimes, ref(primeList), ref(ticketArray), getNextNumber(ticketArray, 11, primeList));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // repopulate the ticket array with the primes from the prime list < sqrtOfUpperBound
    
    for (int i = 0; i < sqrtOfUpperBound; i++) {
        if (primeList[i] == true) {
            ticketArray[i] = false;
        }
    }

    thread t5(findAllPrimes, ref(primeList), ref(ticketArray), 3);  
    thread t6(findAllPrimes, ref(primeList), ref(ticketArray), getNextNumber(ticketArray, 5, primeList));
    thread t7(findAllPrimes, ref(primeList), ref(ticketArray), getNextNumber(ticketArray, 7, primeList));
    thread t8(findAllPrimes, ref(primeList), ref(ticketArray), getNextNumber(ticketArray, 11, primeList));

    t5.join();
    t6.join();
    t7.join();
    t8.join();
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // add up all the primes
    for (int i = 3; i < upperBound; i+=2) {
        if (primeList[i] == true) {
            sum += i;
            numPrimes++;
        }
    }

    //array of 10 highest primes by going through the prime list backwards
    int highestPrimes[10];
    int index = 0;
    for (int i = upperBound - 2; i > 0; i-=2) {
        if (primeList[i] == true) {
            highestPrimes[index] = i;
            index++;
        }
        if (index == 10) {
            break;
        }
    }

    //print out the 10 highest primes to a file names primes.txt
    ofstream myfile;
    myfile.open("primes.txt");
    myfile << "Execution Time: " << duration.count() << "ms" << endl;
    myfile << "Total Primes: " << numPrimes << endl;
    myfile << "Sum of Primes: " << sum << endl;
    myfile << "Highest Primes: [";
    for (int i = 9; i >= 0; i--) {
        if (i != 0) {
            myfile << highestPrimes[i] << ", ";
        } else {
            myfile << highestPrimes[i];
        }
    }
    myfile << "]" << endl;
    myfile.close();

    return 0;

}

void checkNonPrimes(long long start, vector <bool> &primeList) {
      
    for (long long i = start * start; i < sqrtOfUpperBound; i += start) {
        if (primeList[i] == false) {
            continue;
        }
        mtx.lock();
        primeList[i] = false;
        mtx.unlock();
    }
}

int getNextNumber(vector <bool> &ticketArray, int start, vector <bool> &primeList) {
    for (int i = start; i < sqrtOfUpperBound; i++) {
        
        if (ticketArray[i] == false) {
            mtx.lock();
            ticketArray[i] = true;
            mtx.unlock();
            return i;
        } else {
           // check if prime, if so, add i + i-1
           if (primeList[i] == true) {
                i = i + i - 1;
           }
        }
    }
    return -1;
    
}

void findSomePrimes(vector <bool> &primeList, vector <bool> &ticketArray, int start) {
    int nextNumber = start;
    while (nextNumber != -1) {
        checkNonPrimes(nextNumber, primeList);
        nextNumber = getNextNumber(ticketArray, nextNumber + 1, primeList);
    }
}

void checkAllNonePrimes(long long start, vector <bool> &primeList) {
    // find the multiple of start that is greater than sqrtOfUpperBound
    long long multiple = start * start;
    while (multiple < sqrtOfUpperBound) {
        multiple += start;
    }
      
    for (long long i = multiple; i < upperBound; i += start) {
        if (primeList[i] == false) {
            continue;
        }
        mtx.lock();
        primeList[i] = false;
        mtx.unlock();
    }
}

void findAllPrimes(vector <bool> &primeList, vector <bool> &ticketArray, int start) {
    int nextNumber = start;
    while (nextNumber != -1) {
        checkAllNonePrimes(nextNumber, primeList);
        nextNumber = getNextNumber(ticketArray, nextNumber + 1, primeList);
    }
}

void addPrimes(vector <bool> &primeList, int start) {
    long long tempSum = sum;
    long long tempNumPrimes = numPrimes;
    if (start == 1) {
        for (long long i = 3; i < upperBound; i+=2) {
            if (primeList[i] == true) {
                tempSum += i;
                tempNumPrimes++;
            }
        }
        mtx.lock();
        sum = tempSum;
        numPrimes = tempNumPrimes;
        mtx.unlock();
    } else {
        for (long long i = sqrtOfUpperBound; i < upperBound; i+=2) {
            if (primeList[i] == true) {
                tempSum += i;
                tempNumPrimes++;
            }
        }
        mtx.lock();
        sum = tempSum;
        numPrimes = tempNumPrimes;
        mtx.unlock();
    }
    
}


    
