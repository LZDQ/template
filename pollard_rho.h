// mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
ll gcd(ll a, ll b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}

ll fstmul(ll a, ll b, ll m) {
    return (__int128)(a)*b % m;
    // return (a*b-(ll)((long double)(a)/m*b)*m+m)%m;
}

ll fstpw(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = fstmul(res, a, m);
        b >>= 1;
        a = fstmul(a, a, m);
    }
    return res;
}

bool check_prime(ll n) {
    if (n == 1)
        return 0;
    if (!(n & 1))
        return n == 2;
    ll s = n - 1, c = 0;
    while (!(s & 1))
        s >>= 1, c++;
    static const int chkrl[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    static const int chkrs[3] = {2, 7, 61};
    if (n > 0x7fffffff) {
        for (int i = 0; i < 12; i++) {
            if (chkrl[i] >= n)
                break;
            ll u, v = Fstpw(chkrl[i], s, n);
            for (int j = 1; j <= c; j++) {
                u = v;
                v = fstmul(u, u, n);
                if (v == 1) {
                    if (u != 1 && u != n - 1)
                        return 0;
                    break;
                }
            }
            if (v != 1)
                return 0;
        }
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        if (chkrs[i] >= n)
            break;
        ll u, v = Fstpw(chkrs[i], s, n);
        for (int j = 1; j <= c; j++) {
            u = v;
            v = fstmul(u, u, n);
            if (v == 1) {
                if (u != 1 && u != n - 1)
                    return 0;
                break;
            }
        }
        if (v != 1)
            return 0;
    }
    return 1;
}

void pollard_rho(ll n, vector<ll> &res) {
	// Given n, divide it down into prime divisors and push them into res
    if (n == 1)
        return;
    if (!(n & 1))
        return res.push_back(2), pollard_rho(n / 2, res);
    if (check_prime(n)) {
        res.push_back(n);
        return;
    }
    ll c = rnd() % n;
    ll x = rnd() % n, y = x, m = 1;
    int tot = 0;
    for (int k = 1; ; k++) {
        for (int i = 0; i < 1 << k; i++) {
            x = (fstmul(x, x, n) + c) % n;
            y = (fstmul(y, y, n) + c) % n;
            y = (fstmul(y, y, n) + c) % n;
            if (x == y)
                break;
            tot = tot + 1 & 127;
            if (!tot) {
                ll d = gcd(m, n);
                if (d > 1)
                    return pollard_rho(d, res), pollard_rho(n / d, res);
            }
            m = fstmul(m, abs(x - y), n);
        }
        ll d = gcd(m, n);
        if (d > 1)
            return pollard_rho(d, res), pollard_rho(n / d, res);
        if (x == y)
            break;
    }
    return pollard_rho(n, res);
}
