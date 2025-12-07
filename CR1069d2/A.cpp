#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t))
        return 0;

    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        unordered_set<int> S;
        S.reserve(n * 2);

        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            S.insert(a[i]);
        }

        int D0 = (int)S.size();

        int K = INT_MAX;
        for (int x : S)
        {
            if (x >= D0 && x < K)
            {
                K = x;
            }
        }

        cout << K << "\n";
    }

    return 0;
}
