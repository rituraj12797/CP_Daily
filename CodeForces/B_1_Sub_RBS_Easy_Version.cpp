#include <bits/stdc++.h>
using namespace std;
// Constants
#define int long long

// Type definitions
using state = pair<int, int>;
const int mod = 1e9 + 7;

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
int n ;
cin>>n;

string str;
cin>>str;

// for each index i finsd the pos of nest ind j such that str[j] = '('
vector<int> pos(n,0);

int lp = -1;
for(int i = n-1;i>=0;i--) {

    pos[i] = lp;
    if(str[i] == '(') {
        lp = i;
    }
}

// at each index i ==> we have choice 
// ditch the prefix/keep it going 

// if ditch ---> find pos fo next openiing, closing bracets in betwen i---> j-1 = j-i;
// check if (j-i) number of openign bracket exists after j 
// in that case ans = max(ansn n-2*(j-i));

vector<int> num_op(n,0); // number of openmign brakcte fater i index  
int cnt = 0;

for(int i = n -1; i >= 0; i--) {
    num_op[i] = cnt;
    if(str[i] == '(') cnt++;
}

int ans = -1;

for(int i = 0; i < n ; i++) {

    if(str[i] == ')') {
        // we can ditch now 
        int ps = pos[i]; // position of next '('
        if(ps == -1) {
            continue; // beh can't do 
        } else {
            // cout<<" Happened at : "<<i<<"\n";
            // lfgg
            int dif = (ps-i);
            // cout<< "Diif : "<<dif<<"\n";
            if(num_op[ps] >= dif) { // possible
                ans = max(ans, n-2*(dif));
            }
        }
    }
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