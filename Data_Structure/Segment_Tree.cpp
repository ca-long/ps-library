template <class Node>
struct SegTree {
    SegTree(ll n) : n(n), base(bit_ceil(1ULL * n)), seg(2 * base) {}
    SegTree(const vector<Node>& vec) : SegTree(ssize(vec)) {
        for (ll i{ 0 }; i < n; i++) seg[base + i] = vec[i];
        for (ll i{ base - 1 }; i > 0; i--) seg[i] = Node::merge(seg[i << 1], seg[i << 1 | 1]);
    }

    void update(ll i, const Node& x) {
        seg[i += base] = x;
        for (i >>= 1; i > 0; i >>= 1) seg[i] = Node::merge(seg[i << 1], seg[i << 1 | 1]);
    }

    Node query(ll l, ll r) const {
        Node L, R;
        for (l += base, r += base; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = Node::merge(L, seg[l++]);
            if (r & 1) R = Node::merge(seg[--r], R);
        }
        return Node::merge(L, R);
    }

    Node get(ll i) const { return seg[base + i]; }
    Node all() const { return seg[1]; }

    ll walkRight(ll l, auto f) const {
        if (l == n) return n;
        l += base;
        Node acc;
        do {
            while (!(l & 1)) l >>= 1;
            if (!f(Node::merge(acc, seg[l]))) {
                while (l < base) {
                    l <<= 1;
                    if (f(Node::merge(acc, seg[l]))) acc = Node::merge(acc, seg[l++]);
                }
                return l - base;
            }
            acc = Node::merge(acc, seg[l++]);
        } while ((l & -l) != l);
        return n;
    }

    ll walkLeft(ll r, auto f) const {
        if (r == 0) return 0;
        r += base;
        Node acc;
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(Node::merge(seg[r], acc))) {
                while (r < base) {
                    r = r << 1 | 1;
                    if (f(Node::merge(seg[r], acc))) acc = Node::merge(seg[r--], acc);
                }
                return r + 1 - base;
            }
            acc = Node::merge(seg[r], acc);
        } while ((r & -r) != r);
        return 0;
    }

    ll n, base;
    vector<Node> seg;
};

struct SumNode {
    ll x{ 0 };
    SumNode() {}
    SumNode(ll x) : x{ x } {}
    static SumNode merge(const SumNode& L, const SumNode& R) { return SumNode(L.x + R.x); }
};

struct MinNode {
    ll x{ LLONG_MAX }, i{ -1 };
    MinNode() {}
    MinNode(ll x, ll i) : x{ x }, i{ i } {}
    static MinNode merge(const MinNode& L, const MinNode& R) { return R.x < L.x ? R : L; }
};

struct MaxNode {
    ll x{ LLONG_MIN }, i{ -1 };
    MaxNode() {}
    MaxNode(ll x, ll i) : x{ x }, i{ i } {}
    static MaxNode merge(const MaxNode& L, const MaxNode& R) { return R.x > L.x ? R : L; }
};
