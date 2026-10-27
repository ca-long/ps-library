namespace lin {
    const ll MOD = 998'244'353;

    ll binpow(ll a, ll e) {
        a = ((a % MOD) + MOD) % MOD;
        ll res{ 1 };
        while (e) {
            if (e & 1) res = res * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return res;
    }

    ll invmod(ll a) { return binpow(a, MOD - 2); }

    vector<ll> berlekamp_massey(const vector<ll>& vec) {
        ll n{ ssize(vec) };
        if (n == 0) return {};
        
        vector<ll> cur(n), prev(n), tmp;
        cur[0] = prev[0] = 1;

        ll len{ 0 }, gap{ 0 }, perr{ 1 };
        for (ll i{ 0 }; i < n; i++) {
            gap++;

            ll err{ vec[i] % MOD };
            for (ll j{ 1 }; j <= len; j++) err = (err + cur[j] * vec[i - j]) % MOD;

            if (err == 0) continue;
            tmp = cur;

            ll coef{ err * invmod(perr) % MOD };
            for (ll j{ gap }; j < n; j++) cur[j] = (cur[j] - coef * prev[j - gap]) % MOD;

            if (2 * len > i) continue;
            len = i + 1 - len, prev = tmp, perr = err, gap = 0;
        }

        vector<ll> rec(len);
        for (ll i{ 0 }; i < len; i++) rec[i] = (MOD - cur[i + 1]) % MOD;
        return rec;
    }

    ll kitamasa(const vector<ll>& vec, const vector<ll>& rec, ll k) {
        ll n{ ssize(rec) };
        if (n == 0) return 0;
        if (k < ssize(vec)) return vec[k] % MOD;

        auto mul = [&](const vector<ll>& a, const vector<ll>& b) {
            vector<ll> res(2 * n + 1);
            
            for (ll i{ 0 }; i <= n; i++) for (ll j{ 0 }; j <= n; j++) res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
            for (ll i{ 2 * n }; i > n; i--) for (ll j{ 0 }; j < n; j++) res[i - 1 - j] = (res[i - 1 - j] + res[i] * rec[j]) % MOD;

            res.resize(n + 1);
            return res;
        };

        vector<ll> acc(n + 1), base(n + 1);
        acc[0] = base[1] = 1;
        
        for (ll e{ k + 1 }; e; e >>= 1) {
            if (e & 1) acc = mul(acc, base);
            base = mul(base, base);
        }

        ll res{ 0 };
        for (ll i{ 0 }; i < n; i++) res = (res + acc[i + 1] * vec[i]) % MOD;
        return res;
    }
    
    ll guess(const vector<ll>& vec, ll k) { return kitamasa(vec, berlekamp_massey(vec), k); }
}
