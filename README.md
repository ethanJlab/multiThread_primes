# Programming Assignment 1

## How To run
- Run the command ``` g++ -o 100M  sieve.cpp ``` to compile the source code
- Run the executable with the command ``` .\100M.exe ```


In my approach to finding all prime numbers from 1 - 10<sup>8</sup>, I used the Sieve of Eratosthenes to mark all non primes.

My method starts with 2 vector arrays;

PrimeList: a vector of bools that will be marked false if a number is not prime. All numbers start by being marked prime.

ticketArray: a vector of bools that tells whether the number's multiples have been computed yet. 
This acts as a conter so that each thread is given a number to work on that has not been worked on before.

The first 4 threads each start at a prime number and find all prime numbers that are < $\sqrt{n}$
By starting at different primes, this ensures that these 4 threads are approximately doing the same amount of work.

After this, the ticketArray is repopulated with all the Primes < $\sqrt{n}$, and the next 4 threads find all the multiples of these primes < 10<sup>8</sup>.
Although there are fewer elements in the ticket array, these 4 threads are still doing approx the same amount of work because the range for the multiples they need to find is ~10x larger.

At this point, the PrimeList should only contain prime numbers. We can then use this vector to find the number of primes in the range, the sum of the primes, and the top 10 primes.
During testing, this program consistently runs in < 10 sec.

I also tested other values to ensure that the program was working as intended. The following upperbounds were tested below with the following results.

### 1k:
- Execution Time: 1ms
- Total Primes: 168
- Sum of Primes: 76127 
- Highest Primes: [937, 941, 947, 953, 967, 971, 977, 983, 991, 997]


### 10k: 
- Execution Time: 2ms
- Total Primes: 1229
- Sum of Primes: 5736396
- Highest Primes: [9887, 9901, 9907, 9923, 9929, 9931, 9941, 9949, 9967, 9973]


### 1M:
- Execution Time: 84ms
- Total Primes: 78498
- Sum of Primes: 37550402023
- Highest Primes: [999863, 999883, 999907, 999917, 999931, 999953, 999959, 999961, 999979, 999983]

### 100M:
- Execution Time: 8132ms
- Total Primes: 5760227
- Sum of Primes: 279209784650882
- Highest Primes: [99999787, 99999821, 99999827, 99999839, 99999847, 99999931, 99999941, 99999959, 99999971, 99999989]



