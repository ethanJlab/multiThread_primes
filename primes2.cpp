#include <iostream>
#include <thread>
#include <map>
#include <mutex>
using namespace std;
int const upperLimit = 100000000;
int const ticketArrSize = 1250; // sqrt(upperLimit) / 8
int totalNums = upperLimit - 1;
int totalSum = 887459712;
int* totalNumsPtr = &totalNums;
int* totalSumPtr = &totalSum;
mutex mu;

void getWork(int threadIndex, map <int, bool> &isMultiple) {
    int currentNum = 0;
    int ticketArr[ticketArrSize];
    int startingNum;

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

    // get a number from the ticket array and find all the multiples if it < upperLimit

    for (int i = 0; i < ticketArrSize; i++) {
        currentNum = ticketArr[i];
        // check if the currentNum is 0 or 1
        if (currentNum == 0 || currentNum == 1) {
            continue;
        }

        // check if the currentNum is a multiple of any number in the map
        if (isMultiple.find(currentNum) != isMultiple.end()) {
            cout << "current num: " << currentNum << " is a multiple of " << isMultiple[currentNum] << endl;
            continue;
        }

        // find all the multiples of the currentNum < upperLimit
        for (int j = currentNum; j < upperLimit; j += currentNum) {
            // check if j is already in the map
            if (isMultiple.find(j) == isMultiple.end()) {
                cout << "Thread " << threadIndex << " found " << j << " is a multiple of " << currentNum << endl;
                mu.lock();
                //cout << "lock acquired by thread " << threadIndex << endl;
                isMultiple[j] = true;
                totalNums -= 1;
                totalSum -= j;
                mu.unlock();
            } else {
                continue;
            }
        }
        cout << "Thread " << threadIndex << " finished an iteration" << endl;
    }
cout << "Thread " << threadIndex << " is done" << endl;

}

int main() {
    
    map <int, bool> isMultiple;

    thread t1(getWork, 1, ref(isMultiple));
    //t1.join();
    thread t2(getWork, 2, ref(isMultiple));
    //t2.join();
    thread t3(getWork, 3, ref(isMultiple));
    //t3.join();
    thread t4(getWork, 4, ref(isMultiple));
    //t4.join();
    thread t5(getWork, 5, ref(isMultiple));
    //t5.join();
    thread t6(getWork, 6, ref(isMultiple));
   //t6.join();
    thread t7(getWork, 7, ref(isMultiple));
    //t7.join();
    thread t8(getWork, 8, ref(isMultiple));    
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    cout << "Total number of primes: " << totalNums << endl;
    cout << "Sum of all primes: " << totalSum << endl;
    return 0;
}