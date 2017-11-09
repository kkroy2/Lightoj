#include<bits/stdc++.h>
using namespace std;

const int MXN = 100005;
int ar[MXN + 5];
struct data
{
    int mx , mn;
    data()
    {
        mx = -999999999;
        mn = 999999999;
    }
} tree[4*MXN];

data Merge(data a , data b)
{
    data ret;
    ret.mx = max(a.mx ,b.mx);
    ret.mn = min(a.mn, b.mn);
    return ret;
}
void init(int node , int beg , int endd)
{
    if(beg==endd)
    {
        tree[node].mx = ar[beg];
        tree[node].mn = ar[beg];
        return;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;

    init(left , beg , mid);
    init(right, mid+1 , endd);
    tree[node] = Merge(tree[left], tree[right]);
    return;
}
data query(int node , int beg , int endd , int i , int j)
{
    if(i > j)
    {
        data ret;
        ret.mx = -999999999;
        ret.mn = 999999999;
        return ret;
    }
    if(beg==i && endd==j)
    {
        return tree[node];
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;
    data l , r;
    l  = query(left , beg, mid , i , min(j , mid));
    r = query(right , mid+1 , endd, max( i, mid+1) , j);
    return Merge( l ,r);

}
int main()
{
    int tc, cs=0;
    scanf("%d",&tc);
    while(tc--)
    {
        cs++;
        printf("Case %d: ",cs);
        int n, q;
        scanf("%d %d",&n,&q);
        for(int i = 1 ; i <= n ; i++)
            scanf("%d",&ar[i]);
        init(1 , 1, n);
        int res = -999999999;
        for(int i = 1 ; i <= n-q+1; i++)
        {
            data ans = query(1, 1, n,i , i+q - 1);
            res = max(res , ans.mx - ans.mn);
        }
        printf("%d\n",res);
        memset(tree, -1 ,sizeof(tree));
    }
    return 0;
}

