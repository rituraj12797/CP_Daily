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
    int n, m;
    cin>>n>>m;
    vector<vector<char>> graph(n, vector<char>(m));
    vector<pair<int,int>> prtl[26];

    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < m ; j++) {
            cin>>graph[i][j];
            if (graph[i][j] >= 'a' && graph[i][j] <= 'z') {
                prtl[graph[i][j] - 'a'].push_back({i, j});
            }
        }
    }

    pair<int,int> end = {n-1,m-1};

    queue<pair<int,pair<int,int>>> pq; // distance vs cordinates 
    
    vector<vector<int>> dist(n,vector<int>(m,1e9));
    vector<bool> pu(26, false); // won't use gain 
    
    pq.push({0,{0,0}});
    dist[0][0] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while(!pq.empty()) {

        auto a = pq.front();
        pq.pop();

        int dst = -1*a.first;
        int x = a.second.first;
        int y = a.second.second;

        if (dst > dist[x][y]) continue; // djikstra optimise 

        if(end.first == x && end.second == y) {
            cout<<dst<<"\n";
            return ;
        }

        // neghbsr
        for(int i = 0; i <4; i++) {
            int nx = x +dx[i];
            int ny = y+ dy[i];
            if (nx >= 0 && nx < n &&ny >= 0 && ny <m && graph[nx][ny]!='#') {
                if (dist[nx][ny] > dst + 1) {
                    dist[nx][ny] = dst + 1;
                    pq.push({-dist[nx][ny], {nx, ny}});
                }
            }
        }

        // if wrp exists 
        if (graph[x][y] >= 'a' && graph[x][y] <= 'z') {
            int pid = graph[x][y] - 'a';
            if (!pu[pid]) {
                pu[pid] = true; // 
                // trnprt portl  all mind dist becomes same 
                for (auto p : prtl[pid]) {
                    int nx = p.first;
                    int ny = p.second;
                    if (dist[nx][ny] > dst + 1) {
                        dist[nx][ny] = dst + 1;
                        pq.push({-dist[nx][ny], {nx, ny}});
                    }
                }
            }
        }
    }

    cout<<-1<<"\n";
    return ;
}

// Main Function
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin>>t;
    while(t--){solve();}
    return 0;
}