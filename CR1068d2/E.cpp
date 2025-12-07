#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> p;
vector<int> pos;

pair<int, int> query_and_apply(int x, int y)
{
    cout << "? " << x << " " << y << endl;
    cout.flush();

    int u, v;
    if (!(cin >> u >> v))
    {
        exit(0);
    }
    if (u == -1)
        exit(0);

    swap(p[u], p[v]);
    pos[p[u]] = u;
    pos[p[v]] = v;

    return {u, v};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t))
        return 0;
    while (t--)
    {
        cin >> n;
        p.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            cin >> p[i];
        }
        for (int i = 1; i <= n; ++i)
            pos[p[i]] = i;

        for (int i = 1; i <= n / 2; ++i)
        {
            int j = n - i + 1;

            int iter = 0;
            while ((p[i] != i || p[j] != j) && iter < 10000)
            {
                ++iter;
                int pos_i = pos[i];
                int pos_jval = pos[j];

                if (pos_i == j && pos_jval == i)
                {
                    query_and_apply(i, j);
                    continue;
                }

                if (pos_i != i)
                {
                    query_and_apply(pos_i, i);
                    continue;
                }

                if (pos_jval != j)
                {
                    query_and_apply(pos_jval, j);
                    continue;
                }

                query_and_apply(i, j);
            }
        }

        if (n % 2 == 1)
        {
            int center = (n + 1) / 2;
            if (p[center] != center)
            {

                int other = (center == 1 ? 2 : 1);
                query_and_apply(center, other);
                query_and_apply(center, other);
            }
        }

        cout << "!" << endl;
        cout.flush();
    }
    return 0;
}
