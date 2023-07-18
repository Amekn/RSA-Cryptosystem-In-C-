//
//  RSA.cpp
//  RSA Crypto In c++
//
//  Created by Aemon Zhou on 17/07/23.
//


#include <stdexcept>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include "RSA.hpp"
using namespace std;

RSA::RSA(){
    p = primeGenerator(defaultLowerBound, defaultUpperBound);
    //Since we do not want p = q, we will check this.
    q = equivalenceGenerate(p, defaultLowerBound, defaultUpperBound);
    Intialising();
}

RSA::RSA(long long int start, long long int end){
    try{
        p = primeGenerator(start, end);
        q = equivalenceGenerate(p, start, end);
        Intialising();
    }
    catch(invalid_argument e){
        cout << e.what() << endl;
        return;
    }
}

RSA::RSA(const RSA& rsa)
{
    this->p = rsa.p;
    this->q = rsa.q;
    this->N = rsa.N;
    this->N_prime = rsa.N_prime;
    this->e = rsa.e;
    this->d = rsa.d;
}

long long int RSA::encryption(long long int M)
{
    long long int R = modpow(M, e, N);
    return R;
}

long long int RSA::decryption(long long int R)
{
    long long int M = modpow(R, d, N);
    return M;
}

void RSA::Intialising()
{
    //First is to compute N;
    N = p * q;
    //Next is to compute N_prime;
    N_prime = (p - 1) * (q - 1);
    //Next is to compute e;
    bool eFound = false;
    for(e = 2; e <= (N_prime / 2); e++){
        if(gcd(e, N_prime) == 1){
            eFound = true;
            break;
        }
    }
    if(eFound == false) throw invalid_argument("e cannot be found from the prime pairs p and q.");
    //Next is to compute d;
    d = inverse(e, N_prime);
    //Print results;
    char* result = toString();
    cout << result << endl;
    delete[] result;
    result = nullptr;
}

char* RSA::toString()
{
    char* text = new char[200];
    //p
    strcat(text, "p: ");
    char* thisLLT = toStringLLI(p);
    strcat(text, thisLLT);
    strcat(text, "\n");
    delete[] thisLLT;
    //q
    strcat(text, "q: ");
    thisLLT = toStringLLI(q);
    strcat(text, thisLLT);
    strcat(text, "\n");
    delete[] thisLLT;
    //N
    strcat(text, "N: ");
    thisLLT = toStringLLI(N);
    strcat(text, thisLLT);
    strcat(text, "\n");
    delete[] thisLLT;
    //N_prime
    strcat(text, "N': ");
    thisLLT = toStringLLI(N_prime);
    strcat(text, thisLLT);
    strcat(text, "\n");
    delete[] thisLLT;
    //e
    strcat(text, "e: ");
    thisLLT = toStringLLI(e);
    strcat(text, thisLLT);
    strcat(text, "\n");
    delete[] thisLLT;
    //d
    strcat(text, "d: ");
    thisLLT = toStringLLI(d);
    strcat(text, thisLLT);
    strcat(text, "\n");
    delete[] thisLLT;
    thisLLT = nullptr;
    return text;
}

char* RSA::toStringLLI(long long int target){
    char* buffer = new char[20];
    snprintf(buffer, sizeof(buffer), "%lld", target);
    return buffer;
}

long long int RSA::x = 0;
long long int RSA::y = 0;
