#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k;
        cin >> s;
        int last_forced = -1;
        int sleep_count = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                last_forced = max(last_forced, i + k);
            } else {
                if (i <= last_forced) {
                } else {
                    ++sleep_count;
                }
            }
        }
        cout << sleep_count << '\n';
    }
    return 0;
}
