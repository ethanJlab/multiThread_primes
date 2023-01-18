#include <iostream>
#include <thread>
#include <map>
#include <mutex>
#include <chrono>
using namespace std;
using namespace std::chrono;

std::mutex mtx;

const long long upperBound = 100 + 1;
const long long sqrtOfUpperBound = 10 + 1;

long long getTicket(long long ticketArray[sqrtOfUpperBound]);
void checkOffNumber(long long num, long long ticketArray[sqrtOfUpperBound], map <long long,bool> &isMultiple);
void findMultiples(long long num, map <long long,bool> &isMultiple,long long ticketArray[sqrtOfUpperBound]);
void fillMap(map <long long,bool> &isMultiple);
void checkOffTicket (long long num, long long ticketArray[sqrtOfUpperBound]);
void findPrimes(long long startingNum, map <long long,bool> &isMultiple, long long ticketArray[sqrtOfUpperBound]);

int main()
{
    // start timer
    auto start = high_resolution_clock::now();

    long long ticketArray[sqrtOfUpperBound];
    map <long long,bool> isMultiple;

    long long sum;
    // sum of all the number 1 to upperBound
    sum = ((upperBound - 1) * upperBound / 2) - 1;
    long long primeCount = upperBound - 2;
    
    // fill the ticketArray
    ticketArray[0] = 0;
    ticketArray[1] = 0;
    
    for (long long i = 2; i < sqrtOfUpperBound; i++) {
        ticketArray[i] = i;
    }

   
    // find all primes
    /*
    for (long long i = 2; i < sqrtOfUpperBound; i++) {
        if (isMultiple[i] != true) {
            findMultiples(i, isMultiple, ticketArray);
        }
    }
    */
    
    
    // get ticket and find multiples
    
    //findPrimes(isMultiple, ticketArray);
    //create 8 threads and run findPrimes on each
    thread t1(findPrimes, 2, ref(isMultiple), ticketArray);
    thread t2(findPrimes, 3, ref(isMultiple), ticketArray);
    thread t3(findPrimes, 5, ref(isMultiple), ticketArray);
    thread t4(findPrimes, 7, ref(isMultiple), ticketArray);
    //thread t5(findPrimes, 11, ref(isMultiple), ticketArray);
    //thread t6(findPrimes, 13, ref(isMultiple), ticketArray);
    //thread t7(findPrimes, 17, ref(isMultiple), ticketArray);
    //thread t8(findPrimes, 19, ref(isMultiple), ticketArray);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    //t5.join();
    //t6.join();
    //t7.join();
    //t8.join();

    // prlong long all primes
    
    for (long long i = 2; i < upperBound; i++) {
        if (isMultiple[i] == true) {
            //cout << i << endl;
            sum -= i;
            primeCount -= 1;
        }
    }

    cout << "Sum of primes: " << sum << endl;
    cout << "Number of primes: " << primeCount << endl;

    /*for (long long i = 250000; true; i--) {
        if ((i) * (sizeof(bool)) < 65536) {
            cout << "Magic number: " << i << endl;
            break;
        }
    }
    */
    // end timer and prlong long time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: " << endl;
    cout << "Microseconds:" << duration.count() << endl; 
    cout << "Seconds: " << duration.count() / 1000000 << endl;
        
    

    return 0;
}

long long getTicket(long long ticketArray[sqrtOfUpperBound]) {
    // goes through the ticket array and returns the first non-zero number
    for (long long i = 0; i < sqrtOfUpperBound; i++) {
        if (ticketArray[i] != 0) {
            return ticketArray[i];
        }
    }
    return 0;
}

void checkOffNumber(long long num, long long ticketArray[sqrtOfUpperBound], map <long long,bool> &isMultiple) {
    
    // find number in ticketArray and set it to 0
    for (long long i = 0; i < sqrtOfUpperBound; i++) {
        if (ticketArray[i] == num) {
            mtx.lock();
            ticketArray[i] = 0;
            mtx.unlock();            
            break;
        }
    } 
    mtx.lock();
    isMultiple[num] = true;   
    mtx.unlock();
    
}

void checkOffTicket (long long num, long long ticketArray[sqrtOfUpperBound]) {
    for (long long i = 0; i < sqrtOfUpperBound; i++) {
        if (ticketArray[i] == num) {
            mtx.lock();
            ticketArray[i] = 0;
            mtx.unlock();
            break;
        }
    }
} 

void findMultiples(long long num, map <long long,bool> &isMultiple,long long ticketArray[sqrtOfUpperBound]) {
    long long currentNum = num * 2;
   
    checkOffTicket(num, ticketArray); 
    
    for (long long i = currentNum; i < upperBound; i += num){
        checkOffNumber(i, ticketArray, isMultiple);
    }          
    
}

void fillMap(map <long long,bool> &isMultiple) {
    for (long long i = 0; i < upperBound; i++) {
        isMultiple[i] = true;
    }
}

void findPrimes(long long startingNum, map <long long,bool> &isMultiple, long long ticketArray[sqrtOfUpperBound]) {
    long long ticket = startingNum;
    while (ticket != 0) {
        if (isMultiple[ticket] != true) {
            findMultiples(ticket, isMultiple, ticketArray);
        }
        ticket = getTicket(ticketArray);        
    }
}


