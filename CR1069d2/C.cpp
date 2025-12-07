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
        string s, t;
        cin >> s >> t;
        int m = (int)s.size();
        int n = (int)t.size();

        array<int, 26> freqS{}, freqT{};
        freqS.fill(0);
        freqT.fill(0);

        for (char ch : s)
            freqS[ch - 'a']++;
        for (char ch : t)
            freqT[ch - 'a']++;

        bool possible = true;
        for (int i = 0; i < 26; ++i)
        {
            if (freqS[i] > freqT[i])
            {
                possible = false;
                break;
            }
        }

        if (!possible)
        {
            cout << "Impossible\n";
            continue;
        }

        vector<array<int, 26>> suf(m + 1);
        for (int j = 0; j < 26; ++j)
            suf[m][j] = 0;
        for (int i = m - 1; i >= 0; --i)
        {
            suf[i] = suf[i + 1];
            suf[i][s[i] - 'a']++;
        }

        array<int, 26> rem = freqT;
        string ans;
        ans.reserve(n);

        int k = 0;

        for (int pos = 0; pos < n; ++pos)
        {
            for (int c = 0; c < 26; ++c)
            {
                if (rem[c] == 0)
                    continue;

                rem[c]--;

                int k2 = k;
                if (k2 < m && c == s[k2] - 'a')
                {
                    k2++;
                }

                const auto &need = suf[k2];
                bool ok = true;
                for (int x = 0; x < 26; ++x)
                {
                    if (rem[x] < need[x])
                    {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                {
                    ans.push_back(char('a' + c));
                    k = k2;
                    break;
                }
                else
                {
                    rem[c]++;
                }
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
