#include <iostream>
using namespace std;
int main(){
    int sum = 0;
    int N = 1000;
    for (int i=0;i<N;i++){
        if (i%5==0 || i%3 == 0) sum+=i;
    }
    cout << sum;
    return 0;
}
