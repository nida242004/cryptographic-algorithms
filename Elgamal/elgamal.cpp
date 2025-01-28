#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate gcd and coefficients using the Extended Euclidean Algorithm
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

// Function to calculate modular inverse
int modInverse(int a, int m) {
    int x, y;
    int gcd = extendedEuclidean(a, m, x, y);
    if (gcd != 1) {
        throw invalid_argument("Modular inverse does not exist for the given input.");
    }
    return (x % m + m) % m; // Ensure result is positive
}

// Modular exponentiation to calculate (base^exp) % mod efficiently
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

// ElGamal Encryption
pair<int, int> elgamalEncrypt(int plaintext, int e1, int e2, int p, int r) {
    int c1 = modExp(e1, r, p);
    int c2 = (modExp(e2, r, p) * plaintext) % p;
    return {c1, c2};
}

// ElGamal Decryption
int elgamalDecrypt(int c1, int c2, int d, int p) {
    int s = modExp(c1, d, p);
    int s_inv = modInverse(s, p);
    return (c2 * s_inv) % p;
}

int main() {
    // Input values for the ElGamal cryptosystem
    int p, e1, d, r, plaintext;

    cout << "Enter a large prime number (p): ";
    cin >> p;

    cout << "Enter a primitive root modulo p (e1): ";
    cin >> e1;

    cout << "Enter the private key (d): ";
    cin >> d;

    // Calculate the public key
    int e2 = modExp(e1, d, p);
    cout << "Public key (e2): " << e2 << endl;

    cout << "Enter a random number (r) for encryption: ";
    cin >> r;

    cout << "Enter the plaintext (as an integer): ";
    cin >> plaintext;

    // Encryption
    auto [c1, c2] = elgamalEncrypt(plaintext, e1, e2, p, r);
    cout << "\nEncrypted message: (c1, c2) = (" << c1 << ", " << c2 << ")" << endl;

    // Decryption
    int decrypted = elgamalDecrypt(c1, c2, d, p);
    cout << "Decrypted plaintext: " << decrypted << endl;

    return 0;
}
