//
// Created by stefanlin(stefanlin1993@gmail.com) on 2022/1/6.
// Copyright (c) 2022 https://cses.fi/problemset/task/1633 Inc. All rights reserved.
//

#include <stdlib.h>
#include <iostream>

using namespace std;

#define N 1000000
#define ARRAY_SIZE 1000001
#define DICE_SIZE 6
#define MOD 1000000007

uint64_t dp[ARRAY_SIZE];

int main() {
    dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        dp[i] = 0;
        for (int j = 1; j <= DICE_SIZE; ++j) {
            if (i - j < 0) {
                break;
            }
            dp[i] += dp[i - j];
        }
        dp[i] %= MOD;
    }
    int n;
    cin >> n;
    cout << dp[n];
    return 0;
}
