#include<bits/stdc++.h>

using namespace std;


int main()
{
    int tc;
    scanf("%d",&tc);
    int cs = 0;
    int r , c;
    int x,i,j;
        int xr = 0;
    while(tc--)
    {
        cs++;
        scanf("%d %d",&r , &c);
        xr = 0;
        for( i = 0; i < r ; i++)
        {
            for(j = 0; j < c ; j++)
            {
                scanf("%d",&x);
                if((r+c- 2 - i - j)&1)
                {
                    xr ^= x;
                }
            }
        }
        if(xr)
        printf("Case %d: win\n", cs);
        else
        printf("Case %d: lose\n",cs);
    }
    return 0;
}
