#include<bits/stdc++.h>
using namespace std;
#define MXN 100005
int tree[4*MXN];
int ar[MXN];
int n;
void make_tree(int node , int beg , int endd)
{
    if(beg==endd)
    {
        tree[node] = 1;
        return;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;

    make_tree(left , beg , mid);
    make_tree(right , mid+1 , endd);
    tree[node] = tree[left] + tree[right];
    return;
}
int query_tree(int node , int beg , int endd , int val)
{
    if(val==1 && beg==endd )
    {
        tree[node] = 0;
        return beg;
    }

    int left = node << 1;
    int right = left +1 ;
    int mid = (beg+ endd) >> 1;
    int res;
    if(tree[left] < val)
    {
        val -= tree[left];
        res = query_tree(right , mid+1 , endd , val);
    }
    else
    {
        res = query_tree(left , beg , mid , val);
    }

    tree[node] = tree[left] + tree[right];
    return res;
}
int main()
{
    int tc;
    scanf("%d", &tc);
    int cs = 0;
    while(tc--)
    {
        cs++;
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
            scanf("%d",&ar[i]);
        make_tree(1 , 1 , n);
        int r[n+1];
        for(int i = n ; i > 0; i--)
        {
            r[i] = query_tree(1 , 1 , n , i- ar[i]);
        }
        printf("Case %d: %d\n", cs , r[1]);
    }
    return 0;
}
