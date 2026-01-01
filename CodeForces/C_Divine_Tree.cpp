#include<bits/stdc++.h>
using namespace std;
#define int long long 

void solve() {
    int n, m;
    cin>>n>>m;

    if(m < n || m > (n*(n+1))/2 ) {
        cout<<-1<<"\n";
        return ;
    }

    // sums are
    vector<int> sums;
    
    for(int i = 1 ; i <= n; i++) {
        sums.push_back(i*n - (i*(i-1))/2);
    }

    int up = lower_bound(sums.begin(),sums.end(),m) - sums.begin();

    // construct this array 
    vector<int> arr;
    
    for(int i =n; i>= 1; i--) {
        arr.push_back(i);
    }

    // put 1 at the up th index ( 0 based index )
    swap(arr[n-1],arr[up]);

    

    if(sums[up] == m) {
        // for(auto a : arr) cout<<a<<" ";
        // cout<<"\n";  
        cout<<arr[0]<<"\n";
        for(int i = 1; i < n; i++) {
            cout<<arr[i-1]<<" "<<arr[i]<<"\n";
        }
    } else {
        int rem = sums[up] - m;
        // find x = arr[up] - rem
        int x = arr[up-1]-rem;
        int ind = -1;
        for(int i = 0 ; i < n ; i++) {
            if(arr[i] == x) {
                ind= i;
                break;
            }
        }

        swap(arr[up-1],arr[ind]);
        // int num = n;
        // int sum = 0;
        // for(auto a : arr) {
        //     num = min(num,a);
        //     sum += num;
        //     cout<<a<<" ";
        // }
        // cout<<"\n";

        // cout<<sum<<"\n\n";
        cout<<arr[0]<<"\n";
        for(int i = 1; i < n; i++) {
            cout<<arr[i-1]<<" "<<arr[i]<<"\n";
        }

    } 




}

signed main() {
    int t;
    cin>>t;
    while( t--) solve();
}