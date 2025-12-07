

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXK = 365;
const int INF = 2e9;

int dp[MAXK][MAXK];
int next_dp[MAXK][MAXK];
int best_diff[MAXK];

struct Friend
{
    int capacity;
    int weight;
};

void solve()
{
    int n, k;
    if (!(cin >> n >> k))
        return;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<Friend> friends;
    friends.reserve(min(n, k) + 1);

    int max_cap = -1;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] > max_cap)
        {
            friends.push_back({a[i], n - i});
            max_cap = a[i];
        }
    }

    for (int c = 0; c <= k; ++c)
    {
        for (int v = 0; v <= k; ++v)
        {
            dp[c][v] = -1;
        }
    }
    dp[0][0] = 0;

    for (const auto &f : friends)
    {
        int W = f.weight;
        int limit_v = min(f.capacity, k);

        for (int c = 0; c <= k; ++c)
        {
            for (int v = 0; v <= k; ++v)
            {
                next_dp[c][v] = dp[c][v];
            }
        }

        for (int c = 0; c <= k; ++c)
            best_diff[c] = -INF;

        for (int c = 0; c <= k; ++c)
        {
            if (dp[c][0] != -1)
            {
                best_diff[c] = dp[c][0];
            }
        }

        for (int v = 1; v <= limit_v; ++v)
        {
            for (int c = 0; c <= k - v; ++c)
            {
                if (best_diff[c] > -INF)
                {
                    int val = best_diff[c] + v * W;
                    if (val > next_dp[c + v][v])
                    {
                        next_dp[c + v][v] = val;
                    }
                }
            }

            for (int c = 0; c <= k; ++c)
            {
                if (dp[c][v] != -1)
                {
                    int val = dp[c][v] - v * W;
                    if (val > best_diff[c])
                    {
                        best_diff[c] = val;
                    }
                }
            }
        }

        for (int c = 0; c <= k; ++c)
        {
            for (int v = 0; v <= k; ++v)
            {
                dp[c][v] = next_dp[c][v];
            }
        }
    }

    int ans = 0;
    for (int c = 0; c <= k; ++c)
    {
        for (int v = 0; v <= k; ++v)
        {
            if (dp[c][v] > ans)
                ans = dp[c][v];
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t)
    {
        while (t--)
        {
            solve();
        }
    }
    return 0;
}