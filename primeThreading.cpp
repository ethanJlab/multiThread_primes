#include <iostream>
#include <thread>
#include <map>
#include <mutex>
#include <chrono>
using namespace std;
using namespace std::chrono;

std::mutex mtx;

const int upperBound = 1000000 + 1;
const int sqrtOfUpperBound = 1000 + 1;

int getTicket(int ticketArray[sqrtOfUpperBound]);
void checkOffNumber(int num, int ticketArray[sqrtOfUpperBound], map <int,bool> &isMultiple);
void findMultiples(int num, map <int,bool> &isMultiple,int ticketArray[sqrtOfUpperBound]);
void fillMap(map <int,bool> &isMultiple);
void checkOffTicket (int num, int ticketArray[sqrtOfUpperBound]);
void findPrimes(map <int,bool> &isMultiple, int ticketArray[sqrtOfUpperBound]);

int main()
{
    // start timer
    auto start = high_resolution_clock::now();

    int ticketArray[sqrtOfUpperBound];
    map <int,bool> isMultiple;

    int sum;
    // sum of all the number 1 to upperBound
    sum = ((upperBound - 1) * upperBound / 2) - 1;
    int primeCount = upperBound - 2;
    
    // fill the ticketArray
    ticketArray[0] = 0;
    ticketArray[1] = 0;
    
    for (int i = 2; i < sqrtOfUpperBound; i++) {
        ticketArray[i] = i;
    }

   
    // find all primes
    /*
    for (int i = 2; i < sqrtOfUpperBound; i++) {
        if (isMultiple[i] != true) {
            findMultiples(i, isMultiple, ticketArray);
        }
    }
    */
    
    
    // get ticket and find multiples
    // TODo, add starting numbers coresponding to the first 8 primes
    
    //findPrimes(isMultiple, ticketArray);
    //create 8 threads and run findPrimes on each
    thread t1(findPrimes, ref(isMultiple), ticketArray);
    thread t2(findPrimes, ref(isMultiple), ticketArray);
    thread t3(findPrimes, ref(isMultiple), ticketArray);
    thread t4(findPrimes, ref(isMultiple), ticketArray);
    thread t5(findPrimes, ref(isMultiple), ticketArray);
    thread t6(findPrimes, ref(isMultiple), ticketArray);
    thread t7(findPrimes, ref(isMultiple), ticketArray);
    thread t8(findPrimes, ref(isMultiple), ticketArray);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    // print all primes
    
    for (int i = 2; i < upperBound; i++) {
        if (isMultiple[i] == true) {
            //cout << i << endl;
            sum -= i;
            primeCount -= 1;
        }
    }

    cout << "Sum of primes: " << sum << endl;
    cout << "Number of primes: " << primeCount << endl;

    /*for (int i = 250000; true; i--) {
        if ((i) * (sizeof(bool)) < 65536) {
            cout << "Magic number: " << i << endl;
            break;
        }
    }
    */
    // end timer and print time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: " << endl;
    cout << "Microseconds:" << duration.count() << endl; 
    cout << "Seconds: " << duration.count() / 1000000 << endl;
        
    

    return 0;
}

int getTicket(int ticketArray[sqrtOfUpperBound]) {
    // goes through the ticket array and returns the first non-zero number
    for (int i = 0; i < sqrtOfUpperBound; i++) {
        if (ticketArray[i] != 0) {
            return ticketArray[i];
        }
    }
    return 0;
}

void checkOffNumber(int num, int ticketArray[sqrtOfUpperBound], map <int,bool> &isMultiple) {
    
    // find number in ticketArray and set it to 0
    for (int i = 0; i < sqrtOfUpperBound; i++) {
        if (ticketArray[i] == num) {
            ticketArray[i] = 0;            
            break;
        }
    } 

    isMultiple[num] = true;   
    
}

void checkOffTicket (int num, int ticketArray[sqrtOfUpperBound]) {
    for (int i = 0; i < sqrtOfUpperBound; i++) {
        if (ticketArray[i] == num) {
            ticketArray[i] = 0;
            break;
        }
    }
} 

void findMultiples(int num, map <int,bool> &isMultiple,int ticketArray[sqrtOfUpperBound]) {
    int currentNum = num * 2;

    // make mutex
    mtx.lock();
    checkOffTicket(num, ticketArray);
    mtx.unlock();
    
    for (int i = currentNum; i < upperBound; i += num){
        mtx.lock();
        checkOffNumber(i, ticketArray, isMultiple);
        mtx.unlock();
    }          
    
}

void fillMap(map <int,bool> &isMultiple) {
    for (int i = 0; i < upperBound; i++) {
        isMultiple[i] = true;
    }
}

void findPrimes(map <int,bool> &isMultiple, int ticketArray[sqrtOfUpperBound]) {
    int ticket = getTicket(ticketArray);
    while (ticket != 0) {
        if (isMultiple[ticket] != true) {
            findMultiples(ticket, isMultiple, ticketArray);
        }
        ticket = getTicket(ticketArray);        
    }
}


