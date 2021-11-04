 
 
 int dp[100][100];
    void main() {
        int wt[] = {1,3,4,5};
        int val[] = {1,4,5,7};
        int n= 4;
        int w = 10;
        int i,j;
        int res;
    
        for(i=0; i<=n; i++){
            for(j=0; j<=w; j++){
                dp[i][j] = -1;
            }
        }
        res = solve(wt, val, n, w);
        
        printf("Max Profit %d " + res);
        
    }
    
    
   int recursive(int wt[], int val[], int n, int w){

        if(n==0 || w==0)
            return 0;
        
        if( dp[n][w] != -1){
            return dp[n][w];
        }
        if( wt[n-1] <= w){
            dp[n][w] = max( val[n-1] + recursive(wt, val, n-1, w - wt[n-1]), 
                                recursive(wt, val, n-1, w)
                            );
            return dp[n][w];
        }else{
            dp[n][w] = recursive(wt, val, n-1, w);
            return dp[n][w];
        }
        
    }
    
  int memoize(int wt[], int val[], int n, int w){

        if(n==0 || w==0)
            return 0;

        if( wt[n-1] <= w){
            return max( val[n-1] + memoize(wt, val, n-1, w - wt[n-1]), 
                                memoize(wt, val, n-1, w)
                            );
        }else{
            return memoize(wt, val, n-1, w);
        }
        
    }
    
    int solve(int wt[], int val[], int n, int w){

        int dp[n+1][w+1],i,j;
        
        for(i=0; i<=n; i++){
            for(j=0; j<=w; j++){
                
                if(i==0 || j==0){
                    dp[i][j] = 0;
                }
                else if(wt[i-1] <= j){
                    dp[i][j] = max( val[i-1] + dp[i-1][j - wt[i-1]],
                                            dp[i-1][j]);
                }else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][w];
    }
    
    int max(int a,int b){
    	return a>b?a:b;
	}
