#include <bits/stdc++.h>
using namespace std;

long long mod_pow(long long a, long long e, long long mod)
{
    long long r = 1 % mod;
    a %= mod;
    while (e > 0)
    {
        if (e & 1)
            r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T))
        return 0;
    while (T--)
    {
        int n;
        long long m, p;
        cin >> n >> m >> p;

        long long inv = mod_pow(m, p - 2, p);
        int maxRad = n / 2;

        vector<long long> invPow(maxRad + 1);
        vector<long long> prefPow(maxRad + 2);
        vector<long long> prefB(maxRad + 2);

        invPow[0] = 1 % p;
        for (int i = 1; i <= maxRad; ++i)
        {
            invPow[i] = (__int128)invPow[i - 1] * inv % p;
        }

        prefPow[0] = 0;
        prefB[0] = 0;
        for (int k = 0; k <= maxRad; ++k)
        {
            prefPow[k + 1] = prefPow[k] + invPow[k];
            if (prefPow[k + 1] >= p)
                prefPow[k + 1] -= p;

            long long term = (2LL * k + 1) % p;
            term = (__int128)term * invPow[k] % p;
            prefB[k + 1] = prefB[k] + term;
            if (prefB[k + 1] >= p)
                prefB[k + 1] -= p;
        }

        long long S = 0;
        long long Corr = 0;

        auto norm = [&](long long &x)
        {
            x %= p;
            if (x < 0)
                x += p;
        };

        for (int i = 0; i < n; ++i)
        {
            int R = min(i, n - 1 - i) + 1;
            long long S1 = prefPow[R];
            long long B = prefB[R];

            S += S1;
            if (S >= p)
                S -= p;

            long long corr = B - (__int128)S1 * S1 % p;
            norm(corr);
            Corr += corr;
            norm(Corr);
        }

        for (int i = 0; i < n - 1; ++i)
        {
            int maxr = min(i, n - 2 - i);
            int R = maxr + 1;
            long long geo = prefPow[R];
            long long Bgeo = prefB[R];

            long long S1 = (__int128)inv * geo % p;
            long long B = (__int128)inv * Bgeo % p;

            S += S1;
            if (S >= p)
                S -= p;

            long long corr = B - (__int128)S1 * S1 % p;
            norm(corr);
            Corr += corr;
            norm(Corr);
        }

        long long ans = ((__int128)S * S + Corr) % p;
        if (ans < 0)
            ans += p;
        cout << ans << '\n';
    }

    return 0;
}
