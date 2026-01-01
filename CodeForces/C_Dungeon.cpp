#include<bits/stdc++.h>
using namespace std;
#define int long long 


void cinarr(vector<int> &arr) {
    for(int i = 0 ; i < arr.size(); i++) cin>>arr[i];
}

vector<int> arr;
vector<int> mrr;
vector<int> crr;

void solve() {
    int n, m;
    cin>>n>>m;
    
    arr.clear();
    arr.resize(n);

    mrr.clear();
    mrr.resize(m);

    crr.clear();
    crr.resize(m);

    cinarr(arr);
    cinarr(mrr);
    cinarr(crr);

    vector<pair<int,int>> non_zer;
    vector<int> zero;

    for(int i = 0 ; i < m ; i++) {
        if(crr[i] == 0) {
            zero.push_back(mrr[i]);
        } else {
            non_zer.push_back({mrr[i],crr[i]});
        }
    }

    sort(non_zer.begin(),non_zer.end(),[](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.first != b.first) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });
    sort(zero.begin(),zero.end());

    multiset<int> mst;
    for(auto a : arr) mst.insert(a);

    int cnt = 0;

    for(int i = 0 ; i < non_zer.size() ; i++) {
        int mon = non_zer[i].first; // monster health

        auto ptr = (mst.lower_bound(mon));
        
        if(ptr == mst.end()) {
            // no sword os health >= monter health exists ==> exit this lop
            break;
        } else {
            int swrd = *(ptr); // swrd >= mon
            mst.erase(mst.find(swrd)); // this sword got used
            swrd = max(swrd,non_zer[i].second); // replenished sword
            mst.insert(swrd); // insert back

            cnt++; // increment monster killed
        }
    }

    for(int i = 0 ; i < zero.size() && !mst.empty(); ) {

        int swrd = *(mst.begin());
        mst.erase(mst.find(swrd)); // this sword will either kill or be wasted

        if(swrd >= zero[i]) {
            i++;
            cnt++;
        }
    }

    cout<<cnt<<"\n";



    
}

signed main() {
    int t;
    cin>>t;
    while(t--) solve();
}