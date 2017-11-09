#include<bits/stdc++.h>
using namespace std;
const int MXN = 150005;
int ar[MXN];
int tree[4*MXN];
void init(int node, int beg , int endd ,int n)
{
    if(beg==endd)
    {
        if(beg<=n)
            tree[node] = 1;
        else
            tree[node] = 0;
        return;
    }

    int left = node*2;
    int right = left + 1;
    int mid = (beg + endd)/2;

    init(left ,beg , mid , n);
    init(right , mid+1 , endd , n);
    tree[node] = tree[left] + tree[right];
    return;
}
void update(int node  , int beg ,  int endd ,int pos)
{
    if(beg==endd)
    {
        tree[node] = 1;
        return;
    }
    int left = node*2 ;
    int right = left + 1;
    int mid = (beg + endd)/2;
    if(pos <= mid)
        update(left , beg, mid , pos);
    else
        update(right , mid+1 , endd , pos);

    tree[node]= tree[left] + tree[right];
    return;
}
int query(int node , int beg , int endd , int pos)
{
    if(beg==endd)
    {
        tree[node] = 0;
        return ar[beg];
    }

    int left = node*2;
    int right = left + 1;
    int mid = (beg + endd)/2;
    int ans;
    if(tree[left] >= pos)
    {
        ans = query(left , beg , mid , pos);
    }
    else
    {
        ans = query(right,mid+1 , endd ,pos- tree[left]);
    }
    tree[node] = tree[left] + tree[right];
    return ans;
}
int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        printf("Case %d:\n",cs);
        int n , q;
        scanf("%d %d",&n , &q);
        int mx = n+q;
        for(int i = 1 ; i <=n ; i++)
            scanf("%d",&ar[i]);
        init(1 , 1, mx , n);
        for(int i = 0; i < q; i++)
        {
            char ch;
            int pos;
            scanf(" %c %d",&ch , &pos);
            if(ch=='a')
            {
                ar[++n] = pos;
                update(1 , 1, mx , n);
            }
            else
            {
                if(pos > tree[1])
                    printf("none\n");
                else{
                int res = query(1 , 1 , mx , pos);
                printf("%d\n",res);
                }
            }
        }
    }
    return 0;
}
