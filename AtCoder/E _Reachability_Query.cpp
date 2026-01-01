#include<bits/stdc++.h>
using namespace std;
#define int long long 

vector<int> color; // whihc node is of what color 
map<int,int> mp; // root vs number of black color node it has 

struct DSU {
    vector<int> parent;
    vector<int> rank_size;
    int components;
    int n;

    DSU(int N) {
        n = N;
        components = n; 
        rank_size.resize(n + 1, 1);
        parent.resize(n + 1); 

        color.resize(n+1,1);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            mp[i] = 0;
        }
    }

    int find(int x) { // amortized O(log(n))
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    void merge(int x, int y) {
        int ref_a = find(x);
        int ref_b = find(y);

        if (ref_a != ref_b) {
            
            if (rank_size[ref_a] > rank_size[ref_b]) swap(ref_a, ref_b);
            parent[ref_a] = ref_b;
            rank_size[ref_b] += rank_size[ref_a];
            mp[ref_b] += mp[ref_a];
            mp.erase(mp.find(ref_a));
            
            components--; 
        }
    }

    void change_col(int x) {

        int ref_x = find(x);

        if(color[x] == 0) { // black already 
            color[x] = 1;
            mp[find(x)]--;
        } else {
            color[x] = 0;// was white make it black
            mp[find(x)]++;
        }
    }

    bool trvl(int x) {
        return (mp[find(x)] > 0 ? true : false);
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return rank_size[find(x)];
    }
};


void solve() {
    int n, q;
    cin>>n>>q;
    // cout<<n<<" "<<q<<endl;
    DSU ds(n);

    for(int i = 0 ; i <q; i++) {
        int a;
        int b, c;
        cin>>a;

        if(a == 1) {
            cin>>b>>c;
            ds.merge(b,c);    
        } else {
            cin>>b;
            if(a == 2) {
                ds.change_col(b); 
            } else {
                cout<<(ds.trvl(b) ? "Yes":"No")<<"\n";
            }
        }
    }




}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}