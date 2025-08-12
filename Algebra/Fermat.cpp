#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

const int64 MOD = 1000000007LL;
const int64 PHI = MOD - 1; // because MOD is prime

// fast modular exponentiation: base^exp % mod
int64 modpow(int64 base, int64 exp, int64 mod) {
    base %= mod;
    if (base < 0) base += mod;
    int64 res = 1 % mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int64 a, b, c;
        cin >> a >> b >> c;

        // normalize a modulo MOD
        int64 a_mod = ((a % MOD) + MOD) % MOD;

        // Determine if actual exponent (b^c) is zero:
        // - If b == 0 and c > 0 -> exponent == 0
        // - If b == 0 and c == 0 -> exponent == 1 (per problem)
        bool exponent_is_zero = (b == 0 && c > 0);
        bool exponent_is_one  = (b == 0 && c == 0);

        // If a_mod == 0: special handling
        if (a_mod == 0) {
            if (exponent_is_one) {
                // exponent = 1, 0^1 == 0
                cout << 0 << "\n";
            } else if (exponent_is_zero) {
                // exponent = 0, 0^0 defined as 1 in problem
                cout << 1 << "\n";
            } else {
                // exponent >= 1 (b^c positive or b!=0)
                // For example b=1,c=anything -> exponent=1 -> 0^1=0
                // b>0,c>=0 -> exponent positive
                cout << 0 << "\n";
            }
            continue;
        }

        // For a_mod != 0, we can reduce exponent modulo PHI
        // Compute e = b^c mod PHI (PHI = MOD-1)
        // Note: modpow handles the (b==0 && c==0) case returning 1
        int64 b_mod_phi = ((b % PHI) + PHI) % PHI;
        int64 e = modpow(b_mod_phi, c, PHI);

        // But if b==0 && c>0, the actual exponent is 0. modpow(0, c, PHI) returns 0,
        // so e == 0 is correct in that case.
        // If b==0 && c==0, modpow(0,0,PHI) should be treated as 1 -> our modpow returns 1.

        int64 ans = modpow(a_mod, e, MOD);
        cout << ans << "\n";
    }
    return 0;
}
