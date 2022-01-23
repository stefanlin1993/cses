//
// Created by stefanlin(stefanlin1993@gmail.com) on 2022/1/17.
// Copyright (c) 2022 http://www.usaco.org/index.php?page=viewproblem2&cpid=670 Inc. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define H 1001
#define G 1001
#define ALL 2002

int64_t dp[H][G][2];
int64_t x[ALL], y[ALL];

int64_t dis(int i, int j) {
    if (i == 0 || j == 0) {
        return 0x7FFFFFFFF;
    }
    return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

int main() {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);

    int h, g;
    cin >> h >> g;
    for (int i = 1; i <= h + g; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i <= h; ++i) {
        for (int j = 0; j <= g; ++j) {
            dp[i][j][0] = dp[i][j][1] = 0x7FFFFFFFF;
            if (i != 0 && j == 0) {
                dp[i][j][0] = (i == 1 ? 0 : dp[i - 1][j][0] + dis(i, i - 1));
            }
        }
    }

    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= g; ++j) {
            dp[i][j][0] = min({
                dp[i - 1][j][0] + dis(i - 1, i),
                dp[i - 1][j][1] + dis(j + h, i),
                int64_t(0x7FFFFFFFF)
            });
            dp[i][j][1] = min({
                dp[i][j - 1][1] + dis(j - 1 + h, j + h),
                dp[i][j - 1][0] + dis(i, j + h),
                int64_t(0x7FFFFFFFF)
            });
        }
    }

    cout << dp[h][g][0] << endl;
    return 0;
}
