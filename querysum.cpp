#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

int n, q, a[N];
long long st[4 * N];

void build_st(int id, int l, int r) {
    if (l == r) {
        st[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build_st(2 * id, l, mid);
    build_st(2 * id + 1, mid + 1, r);
    st[id] = st[2 * id] + st[2 * id + 1];
}

void update_st(int id, int l, int r, int i, int val) {
    if (l > i || r < i) return;
    if (l == r) {
        st[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    update_st(2 * id, l, mid, i, val);
    update_st(2 * id + 1, mid + 1, r, i, val);
    st[id] = st[2 * id] + st[2 * id + 1];
}

long long get_st(int id, int l, int r, int u, int v) {
    if (l > v || r < u) return 0;
    if (l >= u && r <= v) return st[id];
    int mid = (l + r) / 2;
    long long getl = get_st(2 * id, l, mid, u, v);
    long long getr = get_st(2 * id + 1, mid + 1, r, u, v);
    return getl + getr;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build_st(1, 1, n);
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            a[x] += y;
            update_st(1, 1, n, x, a[x]);
        }
        else cout << get_st(1, 1, n, x, y) << endl;
    }
}