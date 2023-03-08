struct HASH{
  size_t operator()(const pair<int,int> &x) const {
    return hash<int>()(x.first * 7000 + x.second);
  }
};
struct HASH{
  size_t operator()(const vector<vector<int> > &vt) const {
    int v = 0;
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
        v = v * 2 + vt[i][j];
    return hash<int>()(v);
  }
};
unordered_map<pair<int, int>, int, HASH> mp;

// HASH TABLE

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace std;
using namespace __gnu_pbds;

typedef cc_hash_table<pair<int,int>, int, HASH> ht;
ht mp;
mp[{sa,sb}] = 0;
mp.find({na,nb}) != mp.end()
