#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

void solve()
{
    int n;
    long long k;
    cin >> n >> k;

    int initial_popcount = __builtin_popcount(n);

    if (k >= 31)
    {
        cout << initial_popcount - 1 + k << "\n";
        return;
    }

    int limit_k = (int)k;

    int dp[34][2][34];
    for (int i = 0; i < 34; ++i)
    {
        for (int c = 0; c < 2; ++c)
        {
            for (int j = 0; j < 34; ++j)
            {
                dp[i][c][j] = 1e9;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 0; i <= 32; ++i)
    {
        int bit_n = (int)((1LL * n >> i) & 1);

        for (int c = 0; c < 2; ++c)
        {
            for (int cost = 0; cost <= limit_k; ++cost)
            {
                if (dp[i][c][cost] == 1e9)
                    continue;

                {
                    int bit_d = 0;
                    int sum = bit_n + bit_d + c;
                    int res_bit = sum % 2;
                    int next_c = sum / 2;
                    if (cost <= limit_k)
                    {
                        dp[i + 1][next_c][cost] = min(dp[i + 1][next_c][cost], dp[i][c][cost] + res_bit);
                    }
                }

                {
                    int bit_d = 1;
                    int sum = bit_n + bit_d + c;
                    int res_bit = sum % 2;
                    int next_c = sum / 2;
                    int next_cost = cost + 1;
                    if (next_cost <= limit_k)
                    {
                        dp[i + 1][next_c][next_cost] = min(dp[i + 1][next_c][next_cost], dp[i][c][cost] + res_bit);
                    }
                }
            }
        }
    }

    int min_final_pop = 1e9;

    for (int cost = 0; cost <= limit_k; ++cost)
    {
        min_final_pop = min(min_final_pop, dp[33][0][cost]);

        min_final_pop = min(min_final_pop, dp[33][1][cost] + 1);
    }

    cout << initial_popcount - min_final_pop + k << "\n";
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