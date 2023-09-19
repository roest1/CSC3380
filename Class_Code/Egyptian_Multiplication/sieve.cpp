#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <concepts>
#include <iostream>


using namespace std;

/*
Lemmas to sieve:

* The square of the smallest prime factor of a composite number c 
is less than or equal to c

* Any composite number less than p² is sifted (crossed out) a prime < p

* When sifting by p, start marking at p² 

* If we sift numbers up to m, stop sifting when p² ≥ m

Formulas to sieve:

* Value(index i) = 2i + 3

* Index(value v) = (v - 3) / 2

* Index(value(i)²) = 2i² + 6i + 3

*/

template <typename I, typename N>
 //   requires(std::random_access_iterator<I> && std::integral<N>)
void mark_sieve(I first, I last, N factor)
{
    // precondition : Range([first, last) not empty)
    // assert(first != last);

    *first = false; // cross out first composite number

    while (last - first > factor)
    {
        first = first + factor;
        *first = false; // cross out next composite
    }
}

/*
Strength Reduction:
Compiler optimization technique designed to replace 
expensive operations like multiplication with equivalent 
code that uses less expensive operations (ie: addition)
*/

template <typename I, typename N>
 //   requires(std::random_access_iterator<I> && std::integral<N>)
void sift(I first, N n)
{
    I last = first + n;
    std::fill(first, last, true);
    N i = 0;
    N index_square = 3;
    N factor = 3;
    while (index_square < n)
    {
        // invariant: index_square = 2i² + 6i + 3
        // factor = 2i + 3
        if (first[i])
        {
            mark_sieve(first + index_square, last, factor);
        }
        ++i;
        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}

template <typename I, typename N>
 //   requires(std::random_access_iterator<I> && std::integral<N>)
int print_primes(I first, N size)
{
    cout << "1 2";
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (first[i])
        {
            cout << " " << 2*i + 3;
            ++count;
        }
    }
    cout << endl;

    return count;
}




int main()
{
    //const int dataSize = 2147483647;  
    const int dataSize = 1000000;
    vector<bool> bitSieve(dataSize);
    vector<uint8_t> uint8Sieve(dataSize);
    vector<uint16_t> uint16Sieve(dataSize);
    vector<uint32_t> uint32Sieve(dataSize);
    vector<uint64_t> uint64Sieve(dataSize);

    std::chrono::high_resolution_clock::time_point start, end;

    start = chrono::high_resolution_clock::now();
    sift(bitSieve.begin(), dataSize);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Bit Sieve Time: " << duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    sift(uint8Sieve.begin(), dataSize);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "uint8_t Sieve Time: " << duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    sift(uint16Sieve.begin(), dataSize);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "uint16_t Sieve Time: " << duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    sift(uint32Sieve.begin(), dataSize);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "uint32_t Sieve Time: " << duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    sift(uint64Sieve.begin(), dataSize);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "uint64_t Sieve Time: " << duration.count() << " seconds" << endl;


    cout << "===========================================================" << endl;

    const int nMax = 10000000; // 10^7
    const int size = (nMax - 3) / 2;
    bool is_prime[size];

    start = chrono::high_resolution_clock::now();
    
    sift(is_prime, size);
    int primeCount = print_primes(is_prime, size);
    end = chrono::high_resolution_clock::now();
    duration = end - start;

    double approx = static_cast<double>(nMax) / log(static_cast<double>(nMax));

    cout << "n = 10⁷" << ", π(n) = " << primeCount << ", Approximation = " << approx << endl;
    cout << "Execution time: " << duration.count() << " seconds" << endl;
    
    cout << "===========================================================" << endl;


    return 0;
}