#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;

int32_t main(){
    int n, k; cin >> n >> k;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector <int> dep(n + 1), sub(n + 1);
    
    auto init = [&](auto self, int u, int par) -> void{
        sub[u] = 1;
        for (int v : adj[u]) if (v != par){
            dep[v] = dep[u] + 1;
            self(self, v, u);
            sub[u] += sub[v];
        }
    };
    
    init(init, 1, -1);
    
    vector <int> dp1(n + 1);
    dp1[1] = accumulate(dep.begin(), dep.end(), 0LL);
    int sum2 = 0, curr = 0;
    for (int i = 2; i <= n; i++){
        sum2 += curr * sub[i]; sum2 %= mod;
        curr += sub[i]; curr %= mod;
    }
    
    auto dfs = [&](auto self, int u, int par, int h1, int h2) -> void{
        sum2 -= sub[u] * h1; sum2 %= mod;
        sum2 += sub[u] * h2; sum2 %= mod;
        for (int v : adj[u]) if (v != par){
            dp1[v] = dp1[u] - sub[v] + (n - sub[v]);
            int nh1 = h1 + (u != 1) * sub[u]; nh1 %= mod;
            int nh2 = h2 + (u != 1) * (n - sub[u]); nh2 %= mod;
            self(self, v, u, nh1, nh2);
        }  
    };
    
    dfs(dfs, 1, -1, 0, 0);
    int ans = 0;
    
    if (sum2 < 0) sum2 += mod;
    sum2 *= 2; sum2 %= mod;
    
    for (int i = 2; i <= n; i++){
        sum2 += sub[i] * (n - sub[i]); sum2 %= mod;
    }
    
    if (k == 1){
        for (int i = 1; i <= n; i++){
            ans += dp1[i];
            ans %= mod;
        }
        ans *= (n - 2); ans %= mod;
    } else {
        for (int i = 1; i <= n; i++){
            dp1[i] %= mod;
            ans += dp1[i] * dp1[i]; ans %= mod;
        }
        ans += (n - 4 + mod) * sum2 % mod; ans %= mod;
    }
    
    cout << ans << "\n";
}
