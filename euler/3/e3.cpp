#include <iostream>
#include <cmath>

using namespace std;

long smallest_divisor(long n){
    if (n == 1 || n == 2 || n == 3) return 1;
    if (n % 2 == 0) return 2;
    long check = 3;
    long m = sqrt(n) + 1;
    while (check < m) {
        if (n % check == 0) return check;
        check += 2;
    }
    // with no divisors, n must be prime
    return 1;
}

long largest_prime_factor(long n){
    long a = smallest_divisor(n);

    // base case for when n is prime
    if (a == 1) return n;

    // recursively compute prime factors
    long A = largest_prime_factor(a);
    long B = largest_prime_factor(n / a);

    if (A > B) return A;
    return B;
}

int main(int argc, char* argv[]){
    long n = atol(argv[1]);
    cout << "Input: " << n << endl
         << "Largest Prime Factor: " << largest_prime_factor(n) << endl;
    return 0;
}
