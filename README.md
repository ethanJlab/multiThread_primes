# Programming Assignment 1

In my approach to finding all prime numbers from 1 - 10<sup>8</sup>, I used the Sieve of Eratosthenes to mark all non primes.

My method starts with 2 vector arrays;

PrimeList: a vector of bools that will be marked false if a number is not prime. All numbers start by being marked prime.

ticketArray: a vector of bools that tells whether the number's multiples have been computed yet. 
This acts as a conter so that each thread is given a number to work on that has not been worked on before.

The first 4 threads each start at a prime number and find all prime numbers that are < $\sqrt{n}$
By starting at different primes, this ensures that these 4 threads are approximately doing the same amount of work.

After this, the ticketArray is repopulated with all the Primes < $\sqrt{n}$, and the next 4 threads find all the multiples of these primes < 10<sup>8</sup>.
Although there are fewer elements in the ticket array, these 4 threads are still doing approx the same amount of work because teh range for the multiples they need to find is ~10x larger.

At this point, the PrimeList should only contain prime numbers. We can then use this vector to find the number of primes in the range, the sum of the primes, and the top 10 primes.
During testing, this program consistently runs in < 10 sec.
