//
//  RSA.hpp
//  RSA Crypto In c++
//
//  Created by Aemon Zhou on 17/07/23.
//

#ifndef RSA_hpp
#define RSA_hpp

#include <stdio.h>
#include <stdexcept>
#include <random>
#include <limits>
using namespace std;
class RSA{
public:
    RSA();
    RSA(long long int start, long long int end);
    RSA(const RSA& rsa);
    //RSA_Algorithm(const RSA_Algorithm& rsa);
    long long int encryption(long long int M);
    long long int decryption(long long int R);
    void Intialising();
    char* toString();
private:
    long long int p;
    long long int q;
    long long int N;
    long long int N_prime;
    long long int e;
    long long int d;
    static long long int x;
    static long long int y;
    static const long long int defaultLowerBound = 100;
    static const long long int defaultUpperBound = 200;
    static long long int modpow(long long int base, long long int exp, long long int modulus) {
        base %= modulus;
        long long int result = 1;
      while (exp > 0) {
        if (exp & 1) {
        result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp >>= 1;
      }
      return result;
    }
    static void fullGcd(long long int a, long long int b)
    {
        long long int x1, y1;
        if(b == 0)
        {
            x = 1;
            y = 0;
        }
        else
        {
            fullGcd(b, a % b);
            x1 = x; y1 = y;
            x = y1;
            y = x1 - (a / b) * y1;
        }
    }
    static long long int inverse(long long int a, long long int n)
    {
        fullGcd(a, n);
        return (x > 0) ? x : x + n;
    }
    static long long int gcd(long long int a, long long int b)
    {
        if(b == 0)
        {
            return a;
        }
        else
        {
            return gcd(b, a % b);
        }
    }
    static long long int primeGenerator(long long int start, long long int end)
    {
        if(start <= 0 || end <= 0)
        {
            throw invalid_argument("Please ensure start and end are both positive integers.");
        }
        if(start >= end){
            throw invalid_argument("Please ensure start must be smaller than end.");
        }
        long long int prime = randomLLIGenerator(start, end);
        unsigned long long int counter = 0;
        bool isPrime = false;
        while(isPrime == false)
        {
            if(prime <= 1)
            {
                prime = randomLLIGenerator(start, end);
                counter++;
                continue;
            }
            else
            {
                isPrime = true;
                for(long long int i = 2; i <= (prime/2); i++)
                {
                    if((prime % i) == 0)
                    {
                        prime = randomLLIGenerator(start, end);
                        counter++;
                        isPrime = false;
                        break;
                    }
                }
                if(counter > ((end - start)*10))//So we had run 10 times of the size of the difference.
                {
                    throw invalid_argument("Primes cannot be found between the start and end");
                }
            }
        }
        return prime;
    }
    static long long int randomLLIGenerator(long long int start, long long int end)
    {
        random_device rd;
        mt19937_64 eng(rd());
        uniform_int_distribution<unsigned long long int> distr;
        unsigned long long int generated = distr(eng);//Always positive.
        unsigned long long int difference = end - start;//Always positive
        long long int modResult = generated % difference;//Generate an integer within  the range/difference.
        long long int results = start + modResult;
        return results;
    }
    char* toStringLLI(long long int target);
};

#endif /* RSA_hpp */


