#include<bits/stdc++.h>
using namespace std;
#define int long long 


void solve() {
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0 ; i < n ; i++) cin>>arr[i];
    int lm = arr[0];
    set<int> st;
    for(auto a : arr) st.insert(a);


    bool ans= true;
    for(int i = 0 ; i < n - 1 ; i++) {
        lm = min(lm,arr[i]);
        st.erase(st.find(arr[i]));

        int mx = *(st.rbegin());

        if(mx < lm) {
            ans = false;
            break;
        }
    }

    if(ans) cout<<"Yes\n";
    else cout<<"No\n";
}
signed main(){
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
}