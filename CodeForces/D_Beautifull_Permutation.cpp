#include<bits/stdc++.h>
using namespace std;
#define int long long 



void solve() {
    int n;
    cin>>n;

    
    //finding length 
    cout<<"1 "<<1<<" "<<n<<endl;
    int os;
    cin>>os;
    cout<<"2 "<<1<<" "<<n<<endl;
    int ns;
    cin>>ns;

    int length = ns = os; // this is the length 
    
    // finding l 
    int hi = n;
    int lo = 1;
    int mid = lo + (hi - lo)/2;
    int ans = hi;
    while(lo <= hi) {
        cout<<"1 "<<0<<" "<<mid<<endl; // "1 0 mid"
        int sum_orig = 
    }


}

signed main() {
    int t;
    cin>>t;
    while(t--) solve();
}