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
int gcd(int a, int b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm(int a, int b) { return (a / gcd(a, b)) * b; }

int binpow(int a, int b, int m = mod)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

int modinv(int a, int m = mod) { return binpow(a, m - 2, m); }

int pCeil(double value)
{
    const double epsilon = 1e-15;
    if (fabs(value - ceil(value)) < epsilon)
        return static_cast<int>(ceil(value));
    return static_cast<int>(value > 0 ? ceil(value) : value);
}

int pFloor(double value)
{
    const double epsilon = 1e-15;
    if (fabs(value - floor(value)) < epsilon)
        return static_cast<int>(floor(value));
    return static_cast<int>(value < 0 ? floor(value) : value);
}

void sieve(vector<int> &prime, int limit = 200000)
{
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; ++i)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j <= limit; j += i)
            {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= limit; ++i)
    {
        if (is_prime[i])
        {
            prime.push_back(i);
        }
    }
}

// Array/Vector Utility Functions
void printarr(vector<int> &arr)
{
    for (auto x : arr)
        cout << x << " ";
    cout << "\n";
}
void cinarr(vector<int> &arr, int n)
{
    arr.resize(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void isort(vector<int> &arr) { sort(arr.begin(), arr.end()); }
void dsort(vector<int> &arr) { sort(arr.begin(), arr.end(), greater<int>()); }
void csort(vector<int> &arr)
{
    sort(arr.begin(), arr.end(), [](int a, int b)
         { return a < b; });
}

// Map Utility Functions
void print_map(map<int, int> &mp)
{
    for (auto x : mp)
        cout << x.first << " " << x.second << "\n";
}

// Binary Representation
string get_bit_string_32(int x)
{
    string str(32, '0');
    for (int i = 31; i >= 0; i--)
    {
        if (x & (1LL << i))
            str[31 - i] = '1';
    }
    return str;
}

string get_bit_string_64(int x)
{
    string str(64, '0');
    for (int i = 63; i >= 0; i--)
    {
        if (x & (1LL << i))
            str[63 - i] = '1';
    }
    return str;
}

// Characters and Primes
vector<char> charr = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
vector<int> prime_arr;

// Solve Function
void solve()
{
    int n, m;
    cin >> n >> m;

    // white 0 .
    // black 1 #
    vector<vector<int>> arr(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            if (c == '.')
                arr[i][j] = 0;
            else
                arr[i][j] = 1;
        }
    }

    vector<vector<int>> nc(n, vector<int>(m, 0)); // i,j has how many black neighborus

    vector<pair<int, int>> dd = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    function<vector<pair<int, int>>(int, int)> get_neigh = [&](int i, int j) -> vector<pair<int, int>>
    {
        vector<pair<int, int>> neghs;
        for (auto a : dd)
        {

            int x = i + a.first;
            int y = j + a.second;

            if (x >= 0 && x < n && y >= 0 && y < m)
            {
                neghs.push_back({x, y});
                // cout<<"x,y : "<<x<<","<<y<<"\n";
            }
            else
            {
                continue;
            }
        }

        return neghs;
    };

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            vector<pair<int, int>> neigh = get_neigh(i, j);

            for (auto a : neigh)
            {
                if (arr[a.first][a.second] == 1)
                    nc[i][j] += 1;
            }
        }
    }

    queue<pair<int, int>> q;
    vector<vector<int>> vis(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == 1)
                q.push({i, j});
            vis[i][j] = 1;
        }
    }

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;

        arr[x][y] = 1;
        vector<pair<int, int>> in = get_neigh(x, y);

        for (auto x : in)
        {
            if (arr[x.first][x.second] == 0)
            {
                nc[x.first][x.second] += 1;
            }
        }
        q.pop();

        vector<pair<int, int>> ngs = get_neigh(x, y);

        for (auto a : ngs)
        {
            // cout<<" x,y : "<<a.first<<","<<a.second<<"\n";
            vis[a.first][a.second] = 1;

            if (arr[a.first][a.second] == 0)
            {
                // initially white
                // check numebr of neighbour
                if (nc[a.first][a.second] == 1)
                {

                    q.push(a);
                }
            }
        }
    }

    int ans = 0;
    for (auto a : arr)
    {
        printarr(a);
        for (auto b : a)
        {
            if (b == 1)
                ans++;
        }
    }
    cout << ans << "\n";
}

// Main Function
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}