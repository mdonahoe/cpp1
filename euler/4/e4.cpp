#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

void print_vector(vector<int> v){
    // from http://stackoverflow.com/a/11335634/53997
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}

bool is_palindrome(int n){
    vector<int> digits;
    while (n > 0){
        digits.push_back(n % 10);
        n /= 10;
    }
    // print_vector(digits);
    size_t end = digits.size();
    for (size_t i=0; i<end; i++){
        if (digits[i] != digits[end-i-1]) return false;
    }
    return true;
}

int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    int largest = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<=i; j++){
            int p = i * j;
            if (largest < p && is_palindrome(p)) largest = p;
        }
    }
    cout << "largest: " << largest << endl;
    return 0;
}
