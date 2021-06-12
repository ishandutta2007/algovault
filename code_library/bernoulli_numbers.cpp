/***
 *
 * https://en.wikipedia.org/wiki/Bernoulli_number
 *
 * Computes all the bernoulli numbers from 1 to N in O(N^2)
 * Bernoulli numbers are sequence of rational numbers of the form p/q
 * Since the numbers can be huge, they are calculated modulo MOD
 * bernoulli[i] = p * inv(q, MOD) % MOD
 *
***/

#include <bits/stdc++.h>

#define MAX 3010
#define MOD 1000000007

using namespace std;

int S[MAX][MAX], inv[MAX], fact[MAX], bernoulli[MAX];

int expo(long long x, int n){
    long long res = 1;

    while (n){
        if (n & 1) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res % MOD;
}

void gen(){
    int i, j;
    long long x, y, z, lim = (long long)MOD * MOD;

    for (i = 1, fact[0] = 1; i < MAX; i++){
        fact[i] = ((long long) fact[i - 1] * i) % MOD;
    }
    for (i = 0; i < MAX; i++) inv[i] = expo(i, MOD - 2);

    for (i = 1, S[0][0] = 1; i < MAX; i++){
        for (j = 1, S[i][0] = 0; j <= i; j++){
            S[i][j] = ((long long)S[i - 1][j] * j + S[i - 1][j - 1]) % MOD;
        }
    }

    bernoulli[0] = 1;
    for (i = 1; (i + 1) < MAX; i++){
        if (i == 1 || i % 2 == 0){
            for (j = 0, x = 0, y = 0; j <= i; j++){
                z = (long long)fact[j] * inv[j + 1] % MOD;
                z = z * S[i][j] % MOD;
                if (j & 1) y += z;
                else x += z;
            }
            bernoulli[i] = (lim + x - y) % MOD;
        }
    }
}

int main(){
    gen();

    assert(bernoulli[1] == 500000003);
    assert(bernoulli[9] == 0);
    assert(bernoulli[10] == 348484851);  /// bernoulli[10] = 5 / 66 = 5 * 469696973 % 1000000007 = 348484851

    return 0;
}
