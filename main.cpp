#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

long long action(long long left, char op, long long right) {
    if (op == 't') {
        return left + right;
    } else {
        return left * right;
    }
}

long long def(const vector<int>& values, const vector<char>& act, vector<vector<long long>>& dp, int i, int j) {
    if (dp[i][j] != LLONG_MIN) {
        return dp[i][j];
    }
    if (i == j) {
        dp[i][j] = values[i];
        return dp[i][j];
    }
    long long maxim = LLONG_MIN;
    for (int k = i; k < j; k++) {
        long long left = def(values, act, dp, i, k);
        long long right = def(values, act, dp, k + 1, j);
        long long result = action(left, act[k], right);
        maxim = max(maxim, result);
    }
    dp[i][j] = maxim;
    return maxim;
}

int main() {
    int n;
    ifstream in("input.txt");
    in >> n;
    vector<string> data(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        in >> data[i];
    }
    in.close();

    vector<long long> answ;
    for (int i = 0; i < n; i++) {
        int j = (i * 2 + 1) % (2 * n);
        vector<int> values;
        vector<char> act;
        int count = 0;
        while (count < n * 2) {
            if (j % 2 != 0) {
                values.push_back(stoi(data[j]));
            } else {
                act.push_back(data[j][0]);
            }
            j = (j + 1) % (2 * n);
            count++;
        }
        int size = values.size();
        vector<vector<long long>> dp(size, vector<long long>(size, LLONG_MIN));
        long long maxValue = def(values, act, dp, 0, size - 1);
        answ.push_back(maxValue);
    }

    ofstream out("output.txt");
    long long maxik = *max_element(answ.begin(), answ.end());
    out << maxik << endl;
    bool is_first = true;
    for (int i = 0; i < answ.size(); i++) {
        if (answ[i] == maxik) {
            if (!is_first) {
                out << " ";
            } else {
                is_first = false;
            }
            out << i + 1;
        }
    }
    out.close();
    return 0;
}