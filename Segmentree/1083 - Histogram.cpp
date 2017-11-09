#include<bits/stdc++.h>
using namespace std;
#define MXN 30003
int N , ar[30003];
int tree[MXN*4];
void make_tree(int node , int beg , int endd)
{
    if(beg==endd)
    {
        tree[node] = ar[beg];
        return;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd)>>1;

    make_tree(left , beg , mid);
    make_tree(right , mid+1 , endd);
    tree[node] = min(tree[left] , tree[right]);
    return;
}
int leftQuery(int node , int beg , int endd ,int i , int j)// minimum value in the desired range
{
    if(i > j)
        return INT_MAX;
    if( beg == i && endd == j)
    {
        return tree[node];
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;
    int l = leftQuery(left , beg , mid , i ,min( j , mid));
    int r = leftQuery(right , mid+1 , endd , max(i , mid+1) , j);
    return min(r, l);
}
int main()
{
    int tc;
    scanf("%d",&tc);
    int cs = 0;
    while(tc--)
    {
        cs++;
        scanf("%d", &N);
        for(int i = 0; i < N ; i++)
        {
            scanf("%d",&ar[i]);
        }
        make_tree(1 , 0 ,N-1);
        long long res = -1;
        int lm = N-1;
        for(int i = 0; i < N ; i++)
        {
            int left , right ,mid;
            left = i+1;
            right = N-1;
            int r , l ;
            while( (left +1) <  right)
            {
                mid = (left+ right)/2;
                if(leftQuery(1 , 0 , lm , i+1 , mid) >= ar[i])
                {
                    left = mid;
                }
                else
                {
                    right = mid;
                }
            }
            if(leftQuery(1 , 0 , lm , i+1 , right) >= ar[i])
            {
                r = right - i;
            }
            else if(leftQuery(1 , 0 , lm , i+1 , (left+right)/2) >= ar[i])
            {
                r = (left+right)/2 - i;
            }
            else if(leftQuery(1 , 0 , lm , i+1 , left) >= ar[i])
            {
                r = left - i;
            }
            else
            {
                r = 0;
            }

            left = 0;
            right = i-1;
            while( (left +1) <  right)
            {
                mid = (left+ right)/2;
                if(leftQuery(1 , 0 , lm , mid , i-1) >= ar[i])
                {
                    right = mid;
                }
                else
                {
                    left = mid;
                }
            }
            if(leftQuery(1 , 0 , lm , left , i- 1) >= ar[i])
            {
                l = i - left;
            }
            else if(leftQuery(1 , 0 , lm , (left+right)/2 ,i-1 ) >= ar[i])
            {
                l = i - (left+right)/2;
            }
            else if(leftQuery(1 , 0 , lm , right  , i-1) >= ar[i])
            {
                l = i - right;
            }
            else
                l = 0;

            res = max( res , (long long)ar[i]*(long long)(l+r+1));
        }
        printf("Case %d: %lld\n", cs, res);
    }
    return 0;
}
