//
// Created by stefanlin(stefanlin1993@gmail.com) on 2022/1/11.
// Copyright (c) 2022 http://www.usaco.org/index.php?page=viewproblem2&cpid=993 Inc. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int64_t m[1001];
int64_t dp[600][1001];
bool flag[600][1001];

vector<vector<int64_t>> r;

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    int N, M, C;
    cin >> N >> M >> C;
    for (int i = 1; i <= N; ++i) {
        cin >> m[i];
    }
    r.clear();
    r.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        r[b].push_back(a);
    }

    for (int i = 0; i <= 501; ++i) {
        for (int j = 0; j <= N; ++j) {
            flag[i][j] = false;
            dp[i][j] = 0;
        }
    }
    flag[0][1] = true;

    // 边际收益超过501天是负收益
    for (int i = 1; i <= 501; ++i) {
        for (int j = 1; j <= N; ++j) {
            dp[i][j] = 0;
            flag[i][j] = false;
            for (auto c : r[j]) {
                if (flag[i - 1][c]) {
                    if (!flag[i][j]) {
                        flag[i][j] = true;
                        dp[i][j] = dp[i - 1][c];
                        continue;
                    }
                    dp[i][j] = max(dp[i][j], dp[i - 1][c]);
                }
            }
            if (flag[i][j]) {
                dp[i][j] += m[j] - C * (2 * i - 1);
            }
        }
    }

    int64_t result = 0;
    for (int i = 1; i <= 501; ++i) {
        result = max(result, dp[i][1]);
    }

    std::cout << result << std::endl;
    return 0;
}