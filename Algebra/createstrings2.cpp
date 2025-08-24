#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6; // Adjust based on problem constraints

long long fact[MAXN + 1], invfact[MAXN + 1];

// Fast exponentiation (a^b % MOD)
long long modpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i-1] * i) % MOD;

    invfact[MAXN] = modpow(fact[MAXN], MOD - 2); // Fermat's theorem
    for (int i = MAXN - 1; i >= 0; i--)
        invfact[i] = (invfact[i+1] * (i+1)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    string s;
    cin >> s;

    // Count frequencies of each char
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    long long ans = fact[s.size()];
    for (int f : freq) {
        if (f > 0) ans = (ans * invfact[f]) % MOD;
    }

    cout << ans << "\n";
}
