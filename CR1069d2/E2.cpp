#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long power(long long base, long long exp, long long mod)
{
    long long res = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n, long long mod)
{
    return power(n, mod - 2, mod);
}

void solve()
{
    int n;
    long long m, p;
    cin >> n >> m >> p;

    long long inv_m = modInverse(m, p);

    int max_rad = n + 1;

    vector<long long> pm(max_rad + 1);
    pm[0] = 1;
    for (int i = 1; i <= max_rad; ++i)
    {
        pm[i] = (pm[i - 1] * inv_m) % p;
    }

    vector<long long> G(max_rad + 1);
    G[0] = pm[0];
    for (int i = 1; i <= max_rad; ++i)
    {
        G[i] = (G[i - 1] + pm[i]) % p;
    }

    vector<long long> AG_odd(max_rad + 1);
    AG_odd[0] = 1;
    for (int i = 1; i <= max_rad; ++i)
    {
        long long term = ((2LL * i + 1) % p * pm[i]) % p;
        AG_odd[i] = (AG_odd[i - 1] + term) % p;
    }

    vector<long long> AG_even(max_rad + 1);
    AG_even[0] = 0;
    long long current_ag_even = 0;
    for (int i = 1; i <= max_rad; ++i)
    {
        long long term = ((2LL * i - 1) % p * pm[i]) % p;
        current_ag_even = (current_ag_even + term) % p;
        AG_even[i] = current_ag_even;
    }

    long long E_C = 0;
    long long Correction = 0;
    for (int i = 1; i <= n; ++i)
    {
        int max_r = min(i - 1, n - i);

        long long sum_p = G[max_r];
        E_C = (E_C + sum_p) % p;

        long long term_dependent = AG_odd[max_r];
        long long term_independent = (sum_p * sum_p) % p;

        long long diff = (term_dependent - term_independent + p) % p;
        Correction = (Correction + diff) % p;
    }

    for (int i = 1; i < n; ++i)
    {
        int max_r = min(i, n - i);

        long long sum_p = (G[max_r] - 1 + p) % p;
        E_C = (E_C + sum_p) % p;

        long long term_dependent = AG_even[max_r];
        long long term_independent = (sum_p * sum_p) % p;

        long long diff = (term_dependent - term_independent + p) % p;
        Correction = (Correction + diff) % p;
    }

    long long ans = (E_C * E_C) % p;
    ans = (ans + Correction) % p;

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}