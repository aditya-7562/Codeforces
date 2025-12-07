#include <bits/stdc++.h>
using namespace std;

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
        long long k;
        cin >> n >> k;

        vector<int> a(n);
        unordered_set<int> present;
        present.reserve(n * 2);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            if (a[i] <= k)
                present.insert(a[i]);
        }

        vector<int> vals;
        vals.reserve(present.size());
        for (int v : present)
            vals.push_back(v);
        sort(vals.begin(), vals.end());

        unordered_set<int> covered;
        covered.reserve(present.size() * 2);
        vector<int> answer;
        answer.reserve(vals.size());

        for (int b : vals)
        {
            bool ok = true;
            for (long long m = b; m <= k; m += b)
            {
                if (present.find((int)m) == present.end())
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
                continue;

            bool contributes = false;
            for (long long m = b; m <= k; m += b)
            {
                if (present.find((int)m) != present.end() && covered.find((int)m) == covered.end())
                {
                    contributes = true;
                    break;
                }
            }
            if (contributes)
            {
                answer.push_back(b);
                for (long long m = b; m <= k; m += b)
                {
                    if (present.find((int)m) != present.end())
                        covered.insert((int)m);
                }
            }
        }

        bool all_covered = true;
        for (int v : present)
        {
            if (covered.find(v) == covered.end())
            {
                all_covered = false;
                break;
            }
        }

        if (!all_covered)
        {
            cout << -1 << '\n';
        }
        else
        {
            cout << answer.size() << '\n';
            for (size_t i = 0; i < answer.size(); ++i)
            {
                if (i)
                    cout << ' ';
                cout << answer[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
