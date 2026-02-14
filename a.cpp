#include <bits/stdc++.h>
using namespace std;

int main() 
{
    int n, q, S; 
    cin >> n >> q >> S;
    
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    
    vector <int> nxt(n + 1, n + 1), prv(n + 1, 0);
    {
        int p = 1;
        for (int i = 1; i <= n; i++){
            while (p <= n && a[p] <= 2 * a[i]){
                p++;
            }
            nxt[i] = p;
        }
    }
    {
        int p = n;
        for (int i = n; i >= 1; i--){
            while (p >= 1 && a[p] * 2 >= a[i]){
                p--;
            }
            prv[i] = p;
        }
    }
    
    while (q--){
        int l, r; cin >> l >> r;
        
        if (S == 1){
            int k = 0;
            while (l <= r){
                k++;
                l = nxt[l];
            }
            cout << k << "\n";
        } else {
            int ans = 0;
            int store = l;
            while (l <= r){
                ans += 1 - l;
                l = nxt[l];
            }
            l = store;
            while (l <= r){
                ans += r;
                r = prv[r];
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
