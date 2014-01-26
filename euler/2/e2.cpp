#include <iostream>

using namespace std;

int main(){
    int sum = 0;
    int a = 1;
    int b = 2;
    int N = 4000000;
    while (b < N) {
        if (b % 2 == 0) sum += b;
        int tmp = a;
        a = b;
        b += tmp;
    }
    cout << sum << endl;
    return 0;
}
