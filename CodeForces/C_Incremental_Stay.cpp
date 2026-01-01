#include<bits/stdc++.h>
using namespace std;
#define int long long 

void solve() {
    int n;
    cin>>n;
    vector<int> arr(2*n);
    vector<int> ps(2*n,0);

    for(int i = 0 ; i < 2*n; i++) {
        cin>>arr[i];
    }
    sort(arr.begin(),arr.end());

    for(int i = 0 ; i < 2*n; i++) {
        ps[i] = (arr[i] + (i > 0 ? ps[i-1] : 0));
    }
    // for each i from 1 to n
    for(int k = 1 ; k <= n; k++) {

        // add and subtract k sized alternate subarays 

    }
    
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin>>t;
    while(t--) solve();
}