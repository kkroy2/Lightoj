#include<bits/stdc++.h>
#include<stdio.h>
#include<iostream>
using namespace std;
const int mxn = 1008;
int bit[mxn+3][mxn+3];
bool vis[mxn+3][mxn+3];
void update(int idx , int idy , int v)
{
    int x = idx;
    while(x <= mxn)
    {
        int y = idy;
        while( y <= mxn)
        {
            bit[x][y] +=v;
            y += (y&-y);
        }
        x += (x&-x);		
    }
}
int query(int idx ,int idy)
{
    int ret = 0;
    int x = idx;
    while(x)
    {
        int y = idy;
        while(y)
        {
            ret += bit[x][y];
            y -= (y&-y);
        }
        x -= (x&-x);
    }
    return ret;
}
int solve(int x1 , int y1 , int x2 , int y2)
{
    int ans = query(x2 , y2) - query(x2 , y1-1) - query(x1-1 , y2) + query(x1-1 , y1-1);
    return ans;
}
int main()
{
    int tc;
     int cmd , x1, y1 , x2 , y2;
     int q;
     int cs = 0;
    scanf("%d",&tc);
    
    while(tc--)
    {
        cs++;
        
        scanf("%d",&q);
       
        memset(vis , false ,sizeof(vis));
        memset(bit, 0 , sizeof(bit));
        printf("Case %d:\n",cs);
        while(q--)
        {
            scanf("%d",&cmd);
            if(cmd)
            {
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                int ans = solve(x1+1 , y1+1, x2+1 , y2+1);
                printf("%d\n" ,ans);
            }
            else
            {
                scanf("%d%d",&x1,&y1);
                x1++;
                y1++;
                if(!vis[x1][y1])
                {
                    update(x1, y1,1);
                    vis[x1][y1] = true;
                }
            }
        }
    }
    return 0;
}
