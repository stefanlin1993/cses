//
// Created by stefanlin(stefanlin1993@gmail.com) on 2022/1/23.
// Copyright (c) 2022 http://www.usaco.org/index.php?page=viewproblem2&cpid=574 Inc. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define T 5000005

int32_t dp[T];

int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    int32_t t, a, b;
    cin >> t >> a >> b;
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= t; ++i) {
        dp[i] = max(dp[i], i >= a ? dp[i - a] + a : dp[i - 1]);
        dp[i] = max(dp[i], i >= b ? dp[i - b] + b : dp[i - 1]);
    }
    int32_t ans = dp[t];
    for (int i = 1; i <= t; ++i) {
        int32_t x = dp[i] / 2;
        int32_t y = t - x;
        ans = max(ans, x + dp[y]);
    }
    cout << ans << endl;
    return 0;
}
