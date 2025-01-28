#include <iostream>
#include <stdexcept>

using namespace std;

// Function to calculate GCD and coefficients using the Extended Euclidean Algorithm
int extendedEuclidean(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedEuclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Function to calculate the modular inverse of 'a' under modulo 'm'
int modInverse(int a, int m) {
    int x, y;
    int gcd = extendedEuclidean(a, m, x, y);
    if (gcd != 1) {
        throw invalid_argument("Modular inverse does not exist.");
    }
    return (x % m + m) % m; // Ensure the result is positive
}

// Function to perform modular exponentiation (to handle large powers efficiently)
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { // If exponent is odd
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // Square the base
        exp /= 2;
    }
    return result;
}

// Function to perform RSA encryption
int rsaEncrypt(int plaintext, int e, int n) {
    return modExp(plaintext, e, n);
}

// Function to perform RSA decryption
int rsaDecrypt(int ciphertext, int d, int n) {
    return modExp(ciphertext, d, n);
}

int main() {
    int p, q, e;

    cout << "Enter a prime number (p): ";
    cin >> p;
    cout << "Enter another prime number (q): ";
    cin >> q;

    // Calculate n and phi(n)
    int n = p * q;
    int phi_n = (p - 1) * (q - 1);

    cout << "Enter the public key (e): ";
    cin >> e;

    // Ensure 'e' is coprime with phi(n)
    int x, y;
    while (e >= phi_n || extendedEuclidean(e, phi_n, x, y) != 1) {
        cout << "Public key (e) must be coprime with " << phi_n << ". Try another value for e: ";
        cin >> e;
    }

    // Calculate private key 'd'
    int d;
    try {
        d = modInverse(e, phi_n);
    } catch (const invalid_argument& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    // Output public and private keys
    cout << "Public key: (e = " << e << ", n = " << n << ")" << endl;
    cout << "Private key: (d = " << d << ", n = " << n << ")" << endl;

    // Input plaintext
    int plaintext;
    cout << "Enter the plaintext (as an integer): ";
    cin >> plaintext;

    // Encrypt the plaintext
    int ciphertext = rsaEncrypt(plaintext, e, n);
    cout << "Encrypted message: " << ciphertext << endl;

    // Decrypt the ciphertext
    int decryptedPlaintext = rsaDecrypt(ciphertext, d, n);
    cout << "Decrypted plaintext: " << decryptedPlaintext << endl;

    return 0;
}
