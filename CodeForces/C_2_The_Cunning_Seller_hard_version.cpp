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


map<int,int> cost;

int cc(int x) {
    if(x == 0) return 1;
    return 3*cc(x-1);
}

// Solve Function
void solve() {
    int n, k;
    cin>>n>>k;
    // find min configuration then decompose 3^x into 3 entries of 3^x-1 from high to low 
    // maintain a 3^x vs cost map 
    // print_map(cost);
    
    // find the min configurationwhihc solevd the first question 
    
    int num = 1;
    
    for(int i = 0 ; i < 19 ; i++) {
        if(cc(i) <= n) {
            num = cc(i);
        } else break;
    }

    // cout<<" num : "<<num<<endl;
    
    // got the largest power whihc is <= n
    
    priority_queue<int> q;
    
    map<int,int> comps;

    while(n > 0) {
        
        if(n >= num) {
            // cout<<" acceptable : "<<num<<endl;
            n-=num;
            // q.push(num);

            if(comps.find(num) != comps.end()) {
                comps[num] += 1;
            } else {
                comps[num] = 1;
            }

        } else {
            // cout<<" not : "<<num<<endl;
            num/=3;
        }
    }

    int bgs = 0;
    for(auto a : comps) {
        bgs += a.second;
    }

    if(k < bgs) {
        cout<<-1<<"\n"; // minimum number of transactiom me bhi nahi ho rha 
        // cout<<"\n============\n";
        return ;
    }
    
    bool flag = true;

    while(bgs < k) {

        auto it = *(comps.rbegin()); // last element largest 3 power x 

        int num = it.first;
        int turns = it.second;  

        if(num == 1) break;

        int dif = k - bgs; // the number fo extra elements that can be added to this map 

        if(dif >= 2*turns) {
            // as turns entries will be removed and 3 turns will be added 
            comps.erase(comps.find(num));
            comps[num/3] += 3*turns;
            bgs += 2*turns;

        } else {

            // availbe to insert = dif 
            // one remove increments size by 2 means remove dif by 2 whihc will increase total size to bgs -
            comps[num] -= dif/2;
            if(comps[num] == 0) {
                comps.erase(comps.find(num));
            }
            comps[num/3] += 3*(dif/2);

            bgs += dif;
        }
        

        

    }



    int ans = 0;

    for(auto a : comps) {
        ans += a.second*(cost[a.first]);
        // cout<<a.first<<" "<<a.second<<"\n";
    }

    // calculate answer now 

    cout<<ans<<"\n";
    // cout<<"\n============\n";

}

// Main Function
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;

    for(int i = 0 ; i < 19; i++) {
        // i is x 
        int cst = 0;

        if(i == 0) cst = 3;
        else {

            int txo = cc(i+1);
            int txmo = cc(i-1);
            cst = txo + i*txmo;
        }

        cost[cc(i)] = cst;
    }

    cin>>t;
    while(t--){solve();}
    return 0;
}