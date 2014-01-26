#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<int> > matrix;
void record(string input, matrix& M){
    if (input.size() == 1) return;
    string::iterator it = input.begin();
    int first = atoi(&*it);
    cout << "first = " << first << endl;
    for (it++; it < input.end(); it++){
        int cur = atoi(&*it);
        cout << "cur = " << cur << endl;
        M[first][cur] += 1;
    }
    record(input.substr(1), M);
}
void print_matrix(matrix M){
    for (matrix::iterator it = M.begin(); it != M.end(); it++){
        cout << "[ ";
        vector<int> row = (*it);
        for (vector<int>::iterator it2 = row.begin(); it2 != row.end(); it2++){
            cout << (*it2) << " ";
        }
        cout << "]" << endl;
    }
}

#define NUM_DIGITS 10
int main(){
    matrix M;
    M.resize(NUM_DIGITS);
    for (int i=0;i<NUM_DIGITS;i++){
        cout << i << endl;
        M[i].resize(NUM_DIGITS);
    }
    ifstream keylog;
    keylog.open("keylog.txt");
    if (!keylog.is_open()){
        cout << "file open error" << endl;
        return 1;
    }
    string line;
    while (getline(keylog, line)){
        cout << line << endl;
        record(line, M);
    }
    print_matrix(M);
    return 0;
}
