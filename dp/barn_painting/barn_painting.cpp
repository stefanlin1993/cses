//
// Created by stefanlin(stefanlin1993@gmail.com) on 2022/1/16.
// Copyright (c) 2022 http://www.usaco.org/index.php?page=viewproblem2&cpid=766 Inc. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define N 100005
#define MOD 1000000007

vector<vector<int>> m;
vector<int> c;
int64_t dp[N][3];
int ind[N];

bool run(int pos) {
    ind[pos] = 1;

    int flag = 0;
    for (int i : m[pos]) {
        if (c[i] != -1) {
            flag |= (1 << c[i]);
        }
        if (ind[i] == 1) {
            continue;
        }
        if (!run(i)) {
            return false;
        }
        ind[i] = -1;
    }

    if (flag == 7) {
        return false;
    }

    bool can_paint = false;
    for (int i = 0; i < 3; ++i) {
        if (flag & (1 << i)) {
            dp[pos][i] = -2;
            continue;
        }
        if (c[pos] != -1 && c[pos] != i) {
            dp[pos][i] = -2;
            continue;
        }
        bool i_can_paint = true;
        vector<int64_t> ret;
        for (int j : m[pos]) {
            if (ind[j] == 1) {
                continue;
            }
            bool j_can_paint = false;
            bool is_add = false;
            int64_t temp = 0;
            for (int k = 0; k < 3; ++k) {
                if (k == i || dp[j][k] == -2) {
                    continue;
                }
                j_can_paint = true;
                if (dp[j][k] != -1) {
                    is_add = true;
                    temp += dp[j][k];
                }
            }
            if (is_add) {
                ret.push_back(temp % MOD);
            }
            if (!j_can_paint) {
                i_can_paint = false;
                break;
            }
        }
        if (i_can_paint) {
            can_paint = true;
            dp[pos][i] = 1;
            for (int64_t r : ret) {
                dp[pos][i] *= r;
                dp[pos][i] %= MOD;
            }
            if (c[pos] != -1 && ret.size() == 0) {
                dp[pos][i] = -1;
            }
        } else {
            dp[pos][i] = -2;
        }
    }
    return can_paint;
}

int main() {
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);

    int n, k;
    cin >> n >> k;
    m.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        m[x - 1].push_back(y - 1);
        m[y - 1].push_back(x - 1);
    }
    c.resize(n, -1);
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        c[u - 1] = v - 1;
    }

    memset(dp, -1, sizeof dp);
    memset(ind, -1, sizeof ind);

    int64_t result = 0;
    if (run(0)) {
        for (int i = 0; i < 3; ++i) {
            if (dp[0][i] > 0) {
                result += dp[0][i];
            }
        }
        result %= MOD;
    }
    cout << result << endl;
    return 0;
}
