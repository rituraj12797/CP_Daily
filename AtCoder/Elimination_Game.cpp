#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long lastInteger(long long n) {
        long long a = 1;
        long long l = n;
        long long d = 1;
        bool left = true;
        long long cnt = n;
        
        while(cnt > 1) {
            d *= 2;
            cnt = (cnt+1)/2;
            if(left) {
                // turn of left 
                l = a + (cnt-1)*d;
            } else {
                a = l - (cnt - 1)*d;
            }
            left = !left; // chance alternte
        }

        return a; // first element 
    }
};

int main() {
    Solution sol;
    long long n;
    if (cin >> n) {
        cout << sol.lastInteger(n) << endl;
    }
    return 0;
}
