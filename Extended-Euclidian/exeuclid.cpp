#include <iostream>
#include <stdexcept>

using namespace std;

// Function to calculate GCD and coefficients (x, y) using the Extended Euclidean Algorithm
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

// Function to find the modular inverse of 'b' under modulo 'a'
int modularInverse(int b, int a) {
    int x, y;
    int gcd = extendedEuclidean(a, b, x, y);
    if (gcd != 1) {
        throw invalid_argument("Modular inverse does not exist because GCD is not 1.");
    }
    return (y % a + a) % a; // Ensure the result is positive
}

int main() {
    int a, b;
    
    cout << "Enter the first number (a): ";
    cin >> a;
    cout << "Enter the second number (b): ";
    cin >> b;

    int x, y;
    try {
        // Calculate GCD and coefficients
        int gcd = extendedEuclidean(a, b, x, y);
        cout << "GCD of " << a << " and " << b << " is " << gcd << endl;

        // If GCD is 1, calculate and display the modular inverse
        if (gcd == 1) {
            int modInverse = modularInverse(b, a);
            cout << "Modular Inverse of " << b << " under modulo " << a << " is " << modInverse << endl;
        } else {
            cout << "Modular inverse does not exist as GCD is not 1." << endl;
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
