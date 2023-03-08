#include <bits/stdc++.h>
using namespace std;

const int N = 501;
const int LG = 12;

int sparseRow[N][N][LG];
int sparse[N][LG][N][LG];

int plen[N];

void precalc() {
    for (int i = 2; i <= n; i++) {
      plen[i] = plen[i / 2] + 1;
    }
}
int a[N][N];

int getMax(int x1, int y1, int x2, int y2) {
    int rowLen = x2 - x1 + 1, colLen = y2 - y1 + 1;
    int degRow = plen[rowLen], degCol = plen[colLen];
    int newX = x2 + 1 - (1 << degRow);
    int newY = y2 + 1 - (1 << degCol);
    //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << degRow << ' ' << degCol << ' ' << newX << ' ' << newY << endl;
    return max(sparse[y1][degCol][x1][degRow], max(sparse[y1][degCol][newX][degRow], max(sparse[newY][degCol][x1][degRow], sparse[newY][degCol][newX][degRow])));
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    clear(n, m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sparseRow[i][j][0] = a[i][j];
        }
        for (int lg = 1; lg < LG; lg++) {
            for (int j = 1; j + (1 << lg) - 1 <= m; j++) {
                int nj = j + (1 << (lg - 1));
                sparseRow[i][j][lg] = max(sparseRow[i][j][lg - 1], sparseRow[i][nj][lg - 1]);
                //cout << j << ' ' << lg << ' ' << sparseRow[i][j][lg] << endl;
            }
        }
    }

    for (int degCol = 0; degCol < LG; degCol++) {
        for (int j = 1; j + (1 << degCol) - 1 <= m; j++) {
            for (int i = 1; i <= n; i++) {
                sparse[j][degCol][i][0] = sparseRow[i][j][degCol];
            }
            for (int degRow = 1; degRow < 12; degRow++) {
                for (int i = 1; i + (1 << degRow) - 1 <= n; i++) {
                    int ni  = i + (1 << (degRow - 1));
                    sparse[j][degCol][i][degRow] = max(sparse[j][degCol][i][degRow - 1], sparse[j][degCol][ni][degRow - 1]);
                    //cout << i << ' ' << degRow << ' ' << j << ' ' << degCol << ' ' << sparse[j][degCol][i][degRow] << endl;
                }
            }
        }
    }

    int ans = 1e9;
    for (int i = 2; i <= n - 1; i++) {
        for (int j = 2; j <= m - 1; j++) {
            int mx1 = getMax(1, 1, i - 1, j - 1);
            int mx2 = getMax(1, j + 1, i - 1, m);
            int mx3 = getMax(i + 1, 1, n, j - 1);
            int mx4 = getMax(i + 1, j + 1, n, m);
            ans = min(max(mx1, max(mx2, max(mx3, mx4))) - min(mx1, min(mx2, min(mx3, mx4))), ans);
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(NULL), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);

    precalc();
    solve();

    return 0;
}
