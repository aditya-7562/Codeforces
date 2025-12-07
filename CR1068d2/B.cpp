#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t))
        return 0;
    const ll NEG_INF = (ll)-9e18;
    while (t--)
    {
        int n;
        cin >> n;
        vector<ll> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
            cin >> b[i];

        ll X = 0;
        ll Y = NEG_INF;

        for (int i = n; i >= 1; --i)
        {
            ll Xnew = max(X - a[i], (Y == NEG_INF ? NEG_INF : Y - b[i]));
            ll Ynew = max((Y == NEG_INF ? NEG_INF : Y + a[i]), X + b[i]);
            X = Xnew;
            Y = Ynew;
        }
        cout << max(X, Y) << '\n';
    }
    return 0;
}
