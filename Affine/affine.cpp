#include <iostream>
#include <string>
using namespace std;

// Function to calculate GCD
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse of 'a' under modulo 'm'
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    throw invalid_argument("No modular inverse exists!");
}

// Function to encrypt text using Affine Cipher
string affine_encrypt(string text, int a, int b) {
    if (gcd(a, 26) != 1) {
        throw invalid_argument("a and 26 must be coprime.");
    }
    
    string result = "";
    for (char &ch : text) {
        if (isalpha(ch)) {
            char encrypted = ((a * (toupper(ch) - 'A') + b) % 26) + 'A';
            result += encrypted;
        } else {
            result += ch;
        }
    }
    return result;
}

// Function to decrypt text using Affine Cipher
string affine_decrypt(string cipher, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    string result = "";
    
    for (char &ch : cipher) {
        if (isalpha(ch)) {
            char decrypted = ((a_inv * ((toupper(ch) - 'A') - b + 26)) % 26) + 'A';
            result += decrypted;
        } else {
            result += ch;
        }
    }
    return result;
}

int main() {
    string text;
    int a, b;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    cout << "Enter value for 'a' (must be coprime with 26): ";
    cin >> a;
    cout << "Enter value for 'b': ";
    cin >> b;
    
    try {
        string cipher = affine_encrypt(text, a, b);
        cout << "Encrypted text: " << cipher << endl;
        
        string decrypted = affine_decrypt(cipher, a, b);
        cout << "Decrypted text: " << decrypted << endl;
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}
