#include <iostream>
#include <string>
#include <thread>
using namespace std;
int const upperLimit = 100000000;
int const ticketArrSize = 1250; // sqrt(upperLimit) / 8


void getWork(int threadIndex, int* totalNums, int* totalSum) {
    int currentNum = 0;
    int ticketArr[ticketArrSize];
    int startingNum;
    int n ;

    //iteration to find the index of an element in an array

    // depending on the threadIndex, initialize the startingNum
    switch (threadIndex) {
    case 1:
        startingNum = 1;
        break;
    case 2:
        startingNum = 1251;
        break;
    case 3:
        startingNum = 2501;
        break;
    case 4:
        startingNum = 3751;
        break;
    case 5:
        startingNum = 5001;
        break;
    case 6:
        startingNum = 6251;
        break;
    case 7:
        startingNum = 7501;
        break;
    case 8:
        startingNum = 8751;
        break;
    default:
        break;
    }

    // initialize the ticket array
    for (int i = 0; i < ticketArrSize; i++) {
        ticketArr[i] = startingNum;
        startingNum += 1;
    }
    

    // get a number from the ticket array
    for (int i = 0; i < ticketArrSize; i++) {
        if (ticketArr[i] != 0) {
            currentNum = ticketArr[i];
            ticketArr[i] = 0;
        } else {
            continue;
        }
    

        // find all the multiple of that number, for each multiple subtract 1 from the totalNums and subtract the multiple from the totalSum
        for (int j = currentNum; j < upperLimit; j += currentNum) {
            if (j != currentNum) {
                n = sizeof(ticketArr) / sizeof(ticketArr[0]);
                int* itr = find(ticketArr, ticketArr + n, currentNum);
                if (itr != end(ticketArr)) {
                    ticketArr[distance(ticketArr, itr)];
                } else {
                    continue;
                }                
                *totalNums -= 1;
                *totalSum -= j;
            }
        }
    }
}

int main() {
    cout << "Program Start" << endl;
    
    int numberOfPrimes = upperLimit;
    int sum;
    for (int i = 0; i < upperLimit; i++) {
       sum+=i;
    }
    int* primesPtr = &numberOfPrimes;
    int* sumPtr = &sum;

    // create the threads
    thread t1(getWork, 1, primesPtr, sumPtr);
    t1.join();
    thread t2(getWork, 2, primesPtr, sumPtr);
    t2.join();
    thread t3(getWork, 3, primesPtr, sumPtr);
    t3.join();
    thread t4(getWork, 4, primesPtr, sumPtr);
    t4.join();
    thread t5(getWork, 5, primesPtr, sumPtr);
    t5.join();
    thread t6(getWork, 6, primesPtr, sumPtr);
    t6.join();
    thread t7(getWork, 7, primesPtr, sumPtr);
    t7.join();
    thread t8(getWork, 8, primesPtr, sumPtr);
    t8.join();





   
    cout << "Program End" << endl << "Results: " << endl;
    cout << "Number of primes: " << numberOfPrimes << endl;
    cout << "Sum of all the primes:" << sum << endl;

    return 0;

}