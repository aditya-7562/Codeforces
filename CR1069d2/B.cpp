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
        int n, l, r;
        cin >> n >> l >> r;

        int prev = 0;

        for (int i = 1; i <= n; ++i)
        {
            int cur;
            if (i == r)
            {
                cur = l - 1;
            }
            else
            {
                cur = i;
            }
            int ai = prev ^ cur;
            cout << ai << (i == n ? '\n' : ' ');
            prev = cur;
        }
    }
    return 0;
}
