string cvtBase(string s, ll from, ll to) {
    if (s == "" || s == "0") return "0";

    vector<ll> num;
    for (char& c : s) {
        if (c >= '0' && c <= '9') num.push_back(c - '0');
        else num.push_back((c | 32) - 'a' + 10);
    }

    string res;
    ll st{ 0 };

    while (st < num.size()) {
        ll rem{ 0 };

        for (ll i{ st }; i < num.size(); i++) {
            ll cur{ num[i] + rem * from };
            num[i] = cur / to;
            rem = cur % to;
        }

        res += "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rem];

        while (st < num.size() && num[st] == 0) st++;
    }

    reverse(res.begin(), res.end());

    return res;
}
