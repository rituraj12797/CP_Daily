#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
// Constants
#define int long long
#define INT_MAX LONG_LONG_MAX

// Type definitions
using state = pair<int, int>;
const int mod = 1e9 + 7;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

// Mathematical Utility Functions
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm(int a, int b) { return (a / gcd(a, b)) * b; }

int binpow(int a, int b, int m = mod) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

int modinv(int a, int m = mod) { return binpow(a, m - 2, m); }

int pCeil(double value) {
    const double epsilon = 1e-15;
    if (fabs(value - ceil(value)) < epsilon) return static_cast<int>(ceil(value));
    return static_cast<int>(value > 0 ? ceil(value) : value);
}

int pFloor(double value) {
    const double epsilon = 1e-15;
    if (fabs(value - floor(value)) < epsilon) return static_cast<int>(floor(value));
    return static_cast<int>(value < 0 ? floor(value) : value);
}

void sieve(vector<int> &prime, int limit = 200000) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
        }
    }
}

// Array/Vector Utility Functions
void printarr(vector<int> &arr) { for (auto x : arr) cout << x << " "; cout << "\n"; }
void cinarr(vector<int> &arr, int n) { arr.resize(n); for (int i = 0; i < n; i++) cin >> arr[i]; }

void isort(vector<int> &arr) { sort(arr.begin(), arr.end()); }
void dsort(vector<int> &arr) { sort(arr.begin(), arr.end(), greater<int>()); }
void csort(vector<int> &arr) { sort(arr.begin(), arr.end(), [](int a, int b) { return a < b; }); }

// Map Utility Functions
void print_map(map<int, int> &mp) { for (auto x : mp) cout << x.first << " " << x.second << "\n"; }

// Binary Representation
string get_bit_string_32(int x) {
    string str(32, '0');
    for (int i = 31; i >= 0; i--) {
        if (x & (1LL << i)) str[31 - i] = '1';
    }
    return str;
}

string get_bit_string_64(int x) {
    string str(64, '0');
    for (int i = 63; i >= 0; i--) {
        if (x & (1LL << i)) str[63 - i] = '1';
    }
    return str;
}

// Characters and Primes
vector<char> charr = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
vector<int> prime_arr;

// Solve Function
void solve() {
    int n ,m;
    cin>>n>>m;

    vector<vector<pair<int,int>>> graph(n+1);





    for(int i = 0 ; i < m ; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        graph[a].push_back({b,c}); // b se c distance aage 
        graph[b].push_back({a,-1*c}); // a se -1*c distance aage 
    }

    // find components
    vector<int> vis(n+1,0);
    // dfs lambda

    function<void(int, int, int)> dfs = [&](int comp, int node, int par)->void{
        
        if(vis[node] != 0) return;
        vis[node] = comp;


        for(auto a : graph[node]) {
            if(a.first != par) {
                dfs(comp,a.first,node);
            }
        }
    };

    int comp = 0;

    map<int,int> mp; // component number vs root node of that comp
    for(int i = 1 ; i <= n; i++) {
        if(vis[i] == 0) {
            // cout<<" new : "<<i<<"\n";
            comp++;
            mp[comp] = i;
            dfs(comp,i,-1);
        }
    }

    // cout<<comp<<"\n";


    map<int,set<int>> dist; // this reperesnets the set of diatances a node receives via multiple paths from the beginning 
    set<int> vist;


    function<void(int, int, int)> dfsd = [&](int dst, int node, int par)->void{
        
        dist[node].insert(dst);
        if(vist.find(node) != vist.end()) return;
        vist.insert(node);

        for(auto a : graph[node]) {
            if(a.first != par) {
                dfsd(dst + a.second,a.first,node);
            }
        }

    };

    for ( int i = 1 ; i <= comp; i++) {
        // we
        int root = mp[i];
        dist[root].insert(0);
        dfsd(0,root,-1);
    }

    bool flag = true;
    for(int i = 1 ; i <= n; i++) {
        if(dist[i].size() >= 2) flag = false;
    }

    

    // for(int i = 1; i <= n; i++) {
        // cout<<" node : "<<i<<"  dist : ";
        // for(auto a : dist[i]) cout<<a<<" ";
        // cout<<"\n";
    // }

    if(flag) cout<<"YES\n";
    else cout<<"NO\n";


    // nor for each component balance the distance 



    // perfo top sort


    // each independent node give it distance as variables like x1, x2, x3, ....x110....


    // when ever a node becomes independent check if the position of it;s parrent and their di result in same varibles distances or not
    // i,e for a variable x1 there must be same total dist from the very first initia node x1+100,x1+100,x1+100.... this ensures that all mid nodes satisfied it 
    
    // any deviation means some  occoured 
    // for new variable  like distance also came to be x2+50 all distances whihc involve x2 should be sae as x2+50 .... rest will be good 
    // but this multi variate approach wil give tle 
    // instead of this what we can do is 
    // keep one independent node per component ==> we can make anode form independent to dependernt by reversing it's edge and assigining -ve weight to it 

    // a--Xi---->b  consider a is independent and b is depdnedet then we can make a dependent by reversing this edge 
    // a<----(-Xi)------b  now a is independent so like thsi invert the dependancy of each node
    // make the graph undirected in this way it node is made dependent , now pick any node form a components and aign it as teh origin for that component and start a dfs 
    // main tain a ap of int vs set of distnces reachablt till this node 

    // if there are >= 2 distances possible to a node means it is bogus and answer is NO
    // if each has size as 1 ==> yes 


    // for multivariable distance passing this would be a hasstle, what we can do is simply in each components keep a single independent component and make all the other independen component as dependent by reversing their ediges 


}

// Main Function
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin>>t;
    while(t--){solve();}
    return 0;
}