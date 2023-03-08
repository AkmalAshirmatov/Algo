const int maxN = 100224;

struct BIT {
    int data[maxN];
    void update(int idx, int val) {
        while (idx < maxN) {
            data[idx] += val;
            idx += idx & -idx;
        }
    }
    void update(int l, int r, int val) {
        update(l, val);
        update(r + 1, -val);
    }
    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res += data[idx];
            idx -= idx & -idx;
        }
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l);
    }
};

struct LazyBIT {
    BIT bitAdd, bitSub;
    void update(int l, int r, int val) {
        bitAdd.update(l, r, val);
        bitSub.update(l, r, (l - 1) * val);
        bitSub.update(r + 1, (-r + l - 1) * val);
    }
    int query(int idx) {
        return idx * bitAdd.query(idx) - bitSub.query(idx);
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
