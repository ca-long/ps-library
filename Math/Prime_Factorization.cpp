vector<pair<ll, ll>> factorize(ll n) {
    vector<pair<ll, ll>> res;

    auto strip = [&](ll p) {
        ll cnt{ 0 };
        while (n % p == 0) n /= p, cnt++;

        if (cnt) res.push_back({ p, cnt });
    };

    strip(2);
    for (ll i{ 3 }; i <= n / i; i += 2) strip(i);

    if (n > 1) res.push_back({ n, 1 });

    return res;
}
