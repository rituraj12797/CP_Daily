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

vector<vector<int>> dp;

int n;
vector<int> arr;
int rec(int ind, int j) {

    if(ind == n) {
        return 0;
    }

    if(dp[ind][j] != -1) return dp[ind][j];

    int ans = LONG_LONG_MIN;
    // pickleft/  pickrite
    ans = max(ans,arr[ind] + rec(ind+1,j));
    ans = max(ans, -arr[ind] + rec(ind+1,j));
    

    if(j == 1) {
        //  skip
        ans= max(ans,0+rec(ind+1,0));
    }

    return dp[ind][j] = ans;

}

void solve() {
    // int n;
    cin>>n;

    arr.clear();
    arr.resize(n);

    cinarr(arr,n);


    // dp.clear();
    // dp.resize(n+1,vector<int>(2,-1));

    // cout<<rec(0,1)<<"\n";

    // after skipped i all becomes 2nd so all negative 
    vector<int> ps;
    ps.push_back(arr[0]);

    for(int i = 1 ; i < n ; i++) {
        ps.push_back(arr[i] + ps[i-1]);
    }

    int ans = LONG_LONG_MIN;
    
   // choice 1 ==> skip first 
   int ao = -1*(ps[n-1] - arr[0]);
   ans = max(ans,ao);

   // choice 2 ==> skip any other index i

   int otias = 0; // 1 to i - 1 abs sum
   for(int i = 1 ; i < n ; i++) {
    // ans here will be arr[0] ===> taking and it is first so always normal ad 
    // + abs(arr[1]) + ..... abs(arr[i-1]) - ps(i+1 to n-1); and skip i 
    if(i > 1) {
        otias += abs(arr[i-1]);
    }

    int ansh = arr[0]  + otias - (ps[n-1] - ps[i]);
    ans = max(ans,ansh);
   }

   cout<<ans<<"\n";



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