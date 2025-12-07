#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const int MAXN = 150000 + 5;

static ll a_arr[MAXN];
static ll pref[MAXN];
static int run_end[MAXN];

static inline int getCharFast()
{
    static const int BUFSIZE = 1 << 16;
    static char buf[BUFSIZE];
    static int idx = BUFSIZE;
    static int len = BUFSIZE;
    if (idx >= len)
    {
        len = (int)fread(buf, 1, BUFSIZE, stdin);
        idx = 0;
        if (len == 0)
            return EOF;
    }
    return buf[idx++];
}
static inline bool readInt(int &out)
{
    int c;
    while ((c = getCharFast()) <= ' ')
    {
        if (c == EOF)
            return false;
    }
    int sign = 1;
    if (c == '-')
    {
        sign = -1;
        c = getCharFast();
    }
    int val = c - '0';
    while ((c = getCharFast()) > ' ')
        val = val * 10 + (c - '0');
    out = val * sign;
    return true;
}
static inline bool readLongLong(ll &out)
{
    int c;
    while ((c = getCharFast()) <= ' ')
    {
        if (c == EOF)
            return false;
    }
    int sign = 1;
    if (c == '-')
    {
        sign = -1;
        c = getCharFast();
    }
    ll val = c - '0';
    while ((c = getCharFast()) > ' ')
        val = val * 10 + (c - '0');
    out = val * sign;
    return true;
}

static inline int lower_bound_idx_raw(int L, int R, ll target)
{
    int lo = L, hi = R, ans = R + 1;
    while (lo <= hi)
    {
        int mid = (lo + hi) >> 1;
        if (pref[mid] >= target)
        {
            ans = mid;
            hi = mid - 1;
        }
        else
            lo = mid + 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!readInt(T))
        return 0;
    while (T--)
    {
        int n, q;
        readInt(n);
        readInt(q);
        for (int i = 1; i <= n; ++i)
        {
            ll tmp;
            readLongLong(tmp);
            a_arr[i] = tmp;
        }
        pref[0] = 0;
        for (int i = 1; i <= n; ++i)
            pref[i] = pref[i - 1] + a_arr[i];

        run_end[n] = n;
        for (int i = n - 1; i >= 1; --i)
        {
            run_end[i] = (a_arr[i] == a_arr[i + 1]) ? run_end[i + 1] : i;
        }

        for (int qi = 0; qi < q; ++qi)
        {
            int l, r;
            ll x;
            readInt(l);
            readInt(r);
            readLongLong(x);
            ll cnt = 0;
            ll cur = 0;
            while (l <= r)
            {
                ll rem = pref[r] - pref[l - 1];
                if (rem + cur < x)
                {
                    printf("%lld %lld\n", cnt, rem + cur);
                    goto QUERY_DONE;
                }
                if (cur == 0)
                {
                    ll al = a_arr[l];
                    ll need_items = (x + al - 1) / al;
                    int runlast = run_end[l];
                    int available = (runlast < r ? runlast : r) - l + 1;
                    if (available >= need_items)
                    {
                        ll times = available / need_items;
                        cnt += times;
                        l += (int)(times * need_items);
                        continue;
                    }
                }
                ll need = x - cur;
                ll target = pref[l - 1] + need;
                int idx = lower_bound_idx_raw(l, r, target);
                ++cnt;
                cur = 0;
                l = idx + 1;
            }
            printf("%lld %d\n", cnt, 0);
        QUERY_DONE:;
        }
    }
    return 0;
}
