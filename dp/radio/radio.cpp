//
// Created by stefanlin(stefanlin1993@gmail.com) on 2022/1/23.
// Copyright (c) 2022 http://www.usaco.org/index.php?page=viewproblem2&cpid=598 Inc. All rights reserved.
//

#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

#define N 1001

int64_t dp[N][N];
pair<int, int> fm[N];
pair<int, int> bm[N];

pair<int, int> move(char c) {
    pair<int, int> ret;
    if (c == 'N') {
        ret.first = 0;
        ret.second = 1;
    } else if (c == 'S') {
        ret.first = 0;
        ret.second = -1;
    } else if (c == 'E') {
        ret.first = 1;
        ret.second = 0;
    } else if (c == 'W') {
        ret.first = -1;
        ret.second = 0;
    }
    return ret;
}

int energy(int i, int j) {
    int dx = fm[i].first - bm[j].first;
    int dy = fm[i].second - bm[j].second;
    return dx * dx + dy * dy;
}

int main() {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    pair<int, int> f, b;
    cin >> f.first >> f.second;
    cin >> b.first >> b.second;

    string s1, s2;
    cin >> s1 >> s2;

    fm[0] = f;
    for (int i = 1; i <= s1.length(); ++i) {
        fm[i] = move(s1[i - 1]);
        fm[i].first += fm[i - 1].first;
        fm[i].second += fm[i - 1].second;
        // cout << fm[i].first << " " << fm[i].second << endl;
    }
    bm[0] = b;
    for (int i = 1; i <= s2.length(); ++i) {
        bm[i] = move(s2[i - 1]);
        bm[i].first += bm[i - 1].first;
        bm[i].second += bm[i - 1].second;
        // cout << bm[i].first << " " << bm[i].second << endl;
    }

    for (int i = 0; i <= s1.length(); ++i) {
        for(int j = 0; j <= s2.length(); ++j) {
            dp[i][j] = 1e18;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i <= s1.length(); ++i) {
        for (int j = 0; j <= s2.length(); ++j) {
            if (i > 0 && j > 0) {
                dp[i][j] = min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]}) + energy(i, j);
            }
            if (i == 0 && j > 0) {
                dp[i][j] = dp[i][j - 1] + energy(i, j);
            }
            if (j == 0 && i > 0) {
                dp[i][j] = dp[i - 1][j] + energy(i, j);
            }
        }
    }

    cout << dp[s1.length()][s2.length()] << endl;

    return 0;
}
