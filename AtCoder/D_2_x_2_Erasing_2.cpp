#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            if (c == '.')
                arr[i][j] = 1;
            else
                arr[i][j] = 0;
        }
    }

    // BITMASK DP Hard question

   // the greedy intuitive approach of eliminating most dependent black nodes will be wrong as for same dependent nodes the answer may change by changing the order of coloring bits 

   // this leads to an indication fo DP

   // state => row, mask  and dp[row][mask] = the min cost to make all 2x2 subgrids from 0th to ith row as valid while the i-1th row has exact same configuration as the mask 

   // pruning => if row >= n 

   // base case => if n == W-1 then just compute the diff mask this row should take in order to have no 2x2 black sub grid and return it 

   // cache check dp[row][mask]

   // transition => for each row we have the mask fo last row and all the possible new mask for the current row whihc ensures there is no 2x2 subgrid between last and cur row which is completely black 

   // for these we say dp[i][mask] = cost(change cur_row -> new_valid_mask) + rec(row+1,new_valid_mask)

    vector<vector<int>> dp(n+1,vector<int>(256,-1)); // i, 2^w

    auto gen_mask = [&](int cur_row, int prev_row_mask) -> vector<int> {

        // cout<<cur_row<<" prev : "<<prev_row_mask<<endl;
        vector<int> masks;

        for(int i = 0 ; i < (1<<m) ; i++) {
            bool valid = true;



            for(int j = 0 ; j < m; j++) {

                int element = arr[cur_row][j];
                int bit_at_i = (1 & (i>>(m-1-j))); // if here is 1 in the new mask it will return 1 else zero 

                if(element == 1 && bit_at_i == 0) {
                    valid = false;
                }
            }


            for(int j = 1 ; j < m ; j++) {
                int x = (1 & (prev_row_mask>>(m-1-j)));
                int ix = (1 & (i>>(m-1-j))); 

                int y = (1 & (prev_row_mask>>(m-j)));
                int iy = (1 & (i>>(m-j)));


                if(x == 0 && ix == 0 && y == 0 && iy == 0){
                    // cout<<" invalid second "<<endl;
                    valid = false;
                }
            }

            
            // cout<<" valid  : "<<valid<<"\n";

            // cout<<" \n "<<endl;
            if(valid) masks.push_back(i);
        }

       


        return masks;
    };


   function<int(int, int)> rec = [&](int row, int mask) -> int {


        // base case

        // generate valid masks for this rows based on current rows whihc will nto create any 2x2 black grid 

        // cout<<" row : "<<row<<" possible masks : "<<vm.size()<<endl;
        
         if(row == n) { // last row 
            // generate all possible new mask
            return 0;
        }
        
        int cnt = 0;
        for(int i = 0 ; i < m ; i++) if(arr[row][i] == 1) cnt++;
        
        
        
        // cache check 
        if(dp[row][mask] != -1) return dp[row][mask];
        
        // transition from this row to all valid row
        
        // int ans = ;
        vector<int> vm = gen_mask(row,mask); 
        int ans = 1LL*1e7;

        for(auto a : vm) {
            int cost_to_transform = __builtin_popcount(a) - cnt;
            ans = min(ans,cost_to_transform*1LL + rec(row+1,a));
        }

        return dp[row][mask] = ans;
   };


//    our answer is rec(0,last mask)  since we are just starting last mask we can keep as 1111111..... in order to have any choices at the 0th row
   int init_mask = (1<<m) - 1;

   int ans = rec(0,init_mask);

   cout<<ans<<"\n";

//    cout<<"\n==========================\n";

}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
        solve();
}