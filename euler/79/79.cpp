#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main(){

    // open log file
    ifstream keylog;
    keylog.open("keylog.txt");
    if (!keylog.is_open()){
        cout << "file open error" << endl;
        return 1;
    }

    // create codes
    vector<string> codes;
    string line;
    while (getline(keylog, line)){
        codes.push_back(line);
    }

    // iteratively add digits to password
    string password;
    while (codes.size()){

        // score the letters based on position in existing codes
        map<char, int> scores;
        for (auto it=codes.cbegin(); it != codes.end(); it++){
            string code = (*it);
            for (int i=0; i<code.size(); i++){
                char letter = code[i];
                scores[letter] = max(scores[letter], i);
            }
        }

        // find the lowest scoring letter
        auto pr = min_element(scores.begin(), scores.end(),
                              [](const pair<char, int>& p1,
                                 const pair<char, int>& p2) { return p1.second < p2.second; });
        char letter = pr->first;

        // remove letter from all codes
        for (auto it=codes.begin(); it != codes.end(); it++){
            string code = (*it);
            code.erase(remove(code.begin(), code.end(), letter),
                       code.end());
            *it = code;
            // (can i do this directly instead of 2 copies?)
        }

        // remove empty codes
        codes.erase(remove_if(codes.begin(),
                              codes.end(),
                              [](string code){
                                  return (code.size() == 0);
                              }),
                    codes.end());

        // add to password
        password.push_back(letter);
    }
    cout << "password: " << password << endl;
}
