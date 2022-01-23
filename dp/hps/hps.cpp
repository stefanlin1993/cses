//
// Created by stefanlin(stefanlin1993@gmail.com) on 2022/1/17.
// Copyright (c) 2022 http://www.usaco.org/index.php?page=viewproblem2&cpid=694 Inc. All rights reserved.
//

#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define N 100001
#define K 21

int dp[N][K][3];
int ord[26];

int win(int o, int v) {
    return (v + 1) % 3 == o ? 1 : 0;
}

int main() {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    ord[7] = 0, ord[18] = 1, ord[15] = 2;
    memset(dp, 0, sizeof dp);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        string c;
        cin >> c;
        int o = ord[c[0] - 'A'];
        dp[i][0][0] = dp[i - 1][0][0] + win(o, 0);
        dp[i][0][1] = dp[i - 1][0][1] + win(o, 1);
        dp[i][0][2] = dp[i - 1][0][2] + win(o, 2);
        for (int j = 1; j <= k; ++j) {
            dp[i][j][0] = max({dp[i - 1][j][0], dp[i - 1][j - 1][1], dp[i - 1][j - 1][2]}) + win(o, 0);
            dp[i][j][1] = max({dp[i - 1][j][1], dp[i - 1][j - 1][0], dp[i - 1][j - 1][2]}) + win(o, 1);
            dp[i][j][2] = max({dp[i - 1][j][2], dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]}) + win(o, 2);
        }
    }

    int res = 0;
    for (int i = 0; i <= k; ++i) {
        res = max({res, dp[n][i][0], dp[n][i][1], dp[n][i][2]});
    }
    cout << res << endl;
    return 0;
}
