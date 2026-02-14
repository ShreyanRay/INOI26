#include <bits/stdc++.h>
using namespace std;

int main() 
{
    int n; cin >> n;
    vector <int> a(n);
    for (auto &x : a) cin >> x;
    
    sort(a.begin(), a.end());

    int m = (n + 1) / 2;
    int S = n * n;
    vector dp(m + 1, vector(S + 1, vector<long long>(3, 0)));
    dp[0][0][0] = 1;
    
    for (auto x : a){
        auto ndp = dp;
        
        for (int i = 0; i <= m; i++){
            for (int j = 0; j <= S; j++){
                for (int k = 0; k < 3; k++) if (dp[i][j][k]){
                    int ni = i, nj = j, nk = k;
                    if (k == 0){
                        ni++;
                        nj += x;
                    } else if (k == 2){
                        ni--;
                        nj -= x;
                    }
                    
                    if (k == 1){
                        nk = 2;
                    }
                    
                    if (0 <= ni && ni <= m && 0 <= nj && nj <= S){ 
                        ndp[ni][nj][nk] += dp[i][j][k];
                    }
                }
            }
        }
        
        dp = ndp;
        
        for (int i = 0; i <= m; i++){
            for (int j = 0; j <= S; j++){
                dp[i][j][2] += dp[i][j][0];
            }
        }
    }
    
    long long ans = 0;
    for (int j = 1; j <= S; j++){
        ans += dp[1][j][2];
    }
    
    cout << ans << "\n";
}
