#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main () {
    int n;
    cin >> n;
    vector<string> data;
    for (int i = 0; i < 2*n; i++) {
        string in;
        cin >> in;
        data.push_back(in);
    }
}