/***
 *
 * Finds the unique solution x modulo M (product of mods) for which x % mods[i] = ar[i]
 * mods must be pairwise co-prime
 *
***/

#include <bits/stdc++.h>

using namespace std;

/// Bezout's identity, ax + by = gcd(a,b)
long long extended_gcd(long long a, long long b, long long& x, long long& y){
    if (!b){
        y = 0, x = 1;
        return a;
    }

    long long g = extended_gcd(b, a % b, y, x);
    y -= ((a / b) * x);
    return g;
}

long long mod_inverse(long long a, long long m){
    long long x, y, inv;
    extended_gcd(a, m, x, y);
    inv = (x + m) % m;
    return inv;
}

long long CRT(const vector<long long>& ar, const vector<long long>& mods){
    int n = ar.size();

    long long x, y, res = 0, M = 1;
    for (int i = 0; i < n; i++) M *= mods[i];

    for (int i = 0; i < n; i++){
        x = M / mods[i];
        y = mod_inverse(x, mods[i]);
        res = (res + (x * ar[i] % M * y)) % M;
    }

    return res;
}

int main(){
    auto ar = vector<long long>({2, 3, 2});
    auto mods = vector<long long>({3, 5, 7});
    assert(CRT(ar, mods) == 23);

    return 0;
}
