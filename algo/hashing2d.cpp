void ADD(ll &a, ll b, ll MOD) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < MOD) a += MOD;
}

ll MUL(ll a, ll b, ll MOD) {
    return ((a * b) % MOD + MOD) % MOD;
}

struct HS2D {
    ll p, MOD;

    int n, m;
    vector<vector<ll> > hs;
    vector<ll> ppow;
    map<ll, int> mpx, mpy;

    void genHash(vector<vector<char> > &s) {
        n = s.size(), m = s[0].size();
        ll mul = 1;
        hs = vector<vector<ll> >(n, vector<ll>(m));
        ppow = vector<ll>(n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ppow[i * m + j] = mul;
                hs[i][j] = MUL(s[i][j] + 13, mul, MOD);
                if (i > 0) ADD(hs[i][j], hs[i - 1][j], MOD);
                if (j > 0) ADD(hs[i][j], hs[i][j - 1], MOD);
                if (i > 0 && j > 0) ADD(hs[i][j], -hs[i - 1][j - 1], MOD);
                mul = MUL(mul, p, MOD);
            }
        }
    }

    ll getHash(int i1, int j1, int i2, int j2) {
        ll v = hs[i2][j2];
        if (i1 > 0) ADD(v, -hs[i1 - 1][j2], MOD);
        if (j1 > 0) ADD(v, -hs[i2][j1 - 1], MOD);
        if (i1 > 0 && j1 > 0) ADD(v, hs[i1 - 1][j1 - 1], MOD);
        int dif = (n * m - 1) - (i1 * m + j1);
        v = MUL(v, ppow[dif], MOD);
        return v;
    }
};
