// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~WRONG~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~WRONG~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge
{
    int u, v, w, id;
};

struct DSU
{
    vector<int> parent;
    int components;
    DSU(int n)
    {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        components = n;
    }
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j)
        {
            parent[root_i] = root_j;
            components--;
            return true;
        }
        return false;
    }
};

vector<int> tin, tout;
int timer;
vector<vector<pair<int, int>>> adj;
vector<Edge> all_edges;

void dfs(int u, int p)
{
    tin[u] = ++timer;
    for (auto &edge : adj[u])
    {
        int v = edge.first;
        if (v != p)
        {
            dfs(v, u);
        }
    }
    tout[u] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

void solve()
{
    int n, m;
    if (!(cin >> n >> m))
        return;

    all_edges.clear();
    all_edges.reserve(m);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        all_edges.push_back({u, v, w, i});
    }

    sort(all_edges.begin(), all_edges.end(), [](const Edge &a, const Edge &b)
         { return a.w < b.w; });

    DSU dsu(n);
    long long current_sum = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        dsu.unite(all_edges[i].u, all_edges[i].v);
        current_sum += all_edges[i].w;
    }

    if (dsu.components > 1)
    {
        cout << current_sum << "\n";
        return;
    }

    vector<Edge> mst_edges;
    vector<Edge> other_edges;
    mst_edges.reserve(n);
    other_edges.reserve(m - n + 1);

    adj.assign(n + 1, vector<pair<int, int>>());

    for (int i = 0; i < n - 1; ++i)
    {
        mst_edges.push_back(all_edges[i]);
        adj[all_edges[i].u].push_back({all_edges[i].v, i});
        adj[all_edges[i].v].push_back({all_edges[i].u, i});
    }
    for (int i = n - 1; i < m; ++i)
    {
        other_edges.push_back(all_edges[i]);
    }

    if (other_edges.empty())
    {
        cout << "-1\n";
        return;
    }

    tin.resize(n + 1);
    tout.resize(n + 1);
    timer = 0;
    dfs(1, 0);

    struct MstEdgeInfo
    {
        int w;
        int child_node;
    };
    vector<MstEdgeInfo> mst_info;
    mst_info.reserve(n - 1);

    for (auto &e : mst_edges)
    {
        if (is_ancestor(e.u, e.v))
        {
            mst_info.push_back({e.w, e.v});
        }
        else
        {
            mst_info.push_back({e.w, e.u});
        }
    }

    sort(mst_info.begin(), mst_info.end(), [](const MstEdgeInfo &a, const MstEdgeInfo &b)
         { return a.w > b.w; });

    long long ans_diff = -1;
    long long INF_LL = 2e18;
    long long min_diff = INF_LL;

    int LIMIT = 1000;

    int lim_mst = min((int)mst_info.size(), LIMIT);
    for (int i = 0; i < lim_mst; ++i)
    {
        int u_child = mst_info[i].child_node;
        int w_rem = mst_info[i].w;

        for (auto &oe : other_edges)
        {

            bool u_in = is_ancestor(u_child, oe.u);
            bool v_in = is_ancestor(u_child, oe.v);

            if (u_in == v_in)
            {
                long long diff = (long long)oe.w - w_rem;
                if (diff < min_diff)
                    min_diff = diff;
                break;
            }
        }
    }

    int lim_other = min((int)other_edges.size(), LIMIT);
    for (int j = 0; j < lim_other; ++j)
    {
        auto &oe = other_edges[j];

        for (auto &me : mst_info)
        {
            bool u_in = is_ancestor(me.child_node, oe.u);
            bool v_in = is_ancestor(me.child_node, oe.v);

            if (u_in == v_in)
            {
                long long diff = (long long)oe.w - me.w;
                if (diff < min_diff)
                    min_diff = diff;
                break;
            }
        }
    }

    if (min_diff != INF_LL)
    {
        cout << current_sum + min_diff << "\n";
    }
    else
    {
        cout << "-1\n";
    }
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