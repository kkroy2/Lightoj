#include<bits/stdc++.h>
using namespace std;
#define MXN 30003
int ar[MXN] , N;
int tree[4*MXN];
int merge_tree(int x , int y)
{
    if(x==-1)
        return y;
    if(y==-1)
        return x;
    if(ar[x] < ar[y])
        return x;
    return y;
}
void make_tree(int node , int beg , int endd)
{
    if(beg==endd)
    {
        tree[node] = beg;
        return;
    }

    int left = node << 1;
    int mid = (beg+ endd)>>1;
    make_tree(left , beg , mid);
    make_tree(left+1 , mid+1 , endd);
    tree[node] = merge_tree(tree[left] , tree[left+1]);
    return;
}

int query(int node , int beg , int endd , int i , int j)
{
    //cout<<i << " "<<j<<endl;
    if(i > j)
        return -1;
    if(beg==i && endd == j)
        return tree[node];
    int left = node << 1;
    int mid = (beg + endd)>>1;
    int l = query(left , beg , mid , i , min(mid , j));
    int r = query(left+1 , mid+1 , endd , max(mid+1 , i) ,j);
    return merge_tree(l , r);
}
int solve(int x , int y)
{
    //cout<<x<<" "<<y<<endl;
    if(x > y)
        return -1;
    if(x==y)
        return ar[x];
    int minIndex = query(1 , 0 , N-1 , x ,y);
   // cout<<minIndex<<endl;
    int ret = max( solve(x , minIndex - 1) , solve(minIndex+1 , y));
    return max( ret , ar[minIndex]*(y-x+1));
}
int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        cin>>N;
        for(int i = 0; i < N ; i++)
            scanf("%d",&ar[i]);
        make_tree(1 , 0 , N-1 );
        int res = solve(0 , N-1);
        cout<<"Case "<<cs<<": "<<res<<endl;
    }
    return 0;
}
