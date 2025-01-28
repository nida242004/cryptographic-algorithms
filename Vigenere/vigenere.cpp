#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to encrypt text using the Vigenère cipher
string vigenere_encrypt(const string& text, const string& key) {
    string encrypted;
    int key_index = 0;
    for (char char_in_text : text) {
        if (isalpha(char_in_text)) {
            // Convert character to uppercase for uniformity
            char char_upper = toupper(char_in_text);
            int shift = toupper(key[key_index]) - 'A';
            encrypted += char(((char_upper - 'A' + shift) % 26) + 'A');
            key_index = (key_index + 1) % key.length();
        } else {
            encrypted += char_in_text;
        }
    }
    return encrypted;
}

// Function to decrypt text using the Vigenère cipher
string vigenere_decrypt(const string& cipher, const string& key) {
    string decrypted;
    int key_index = 0;
    for (char char_in_cipher : cipher) {
        if (isalpha(char_in_cipher)) {
            // Convert character to uppercase for uniformity
            char char_upper = toupper(char_in_cipher);
            int shift = toupper(key[key_index]) - 'A';
            decrypted += char(((char_upper - 'A' - shift + 26) % 26) + 'A');
            key_index = (key_index + 1) % key.length();
        } else {
            decrypted += char_in_cipher;
        }
    }
    return decrypted;
}

int main() {
    string text, key;

    cout << "Enter text to encrypt: ";
    getline(cin, text);

    cout << "Enter the encryption key: ";
    getline(cin, key);

    // Encrypt the text
    string cipher = vigenere_encrypt(text, key);
    cout << "Encrypted text: " << cipher << endl;

    // Decrypt the ciphered text
    string decrypted = vigenere_decrypt(cipher, key);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
