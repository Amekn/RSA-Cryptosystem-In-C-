//
//  main.cpp
//  RSA Crypto In c++
//
//  Created by Aemon Zhou on 17/07/23.
//

#include <iostream>
#include "RSA.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    RSA* r1 = new RSA();
    long long int plaintext = 1781;
    long long int ciphertext = r1->encryption(plaintext);
    cout << "Encrypted text from " << plaintext << " to " << ciphertext << endl;
    long long int decrypted = r1->decryption(ciphertext);
    cout << "Decrypted text from " << ciphertext << " to " << decrypted << endl;
    return 0;
}
