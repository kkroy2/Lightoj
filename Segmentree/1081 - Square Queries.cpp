#include<bits/stdc++.h>
using namespace std;
#define MXN 505
int ar[MXN][MXN];
int n , m;

struct data
{
    int subTree[4*MXN], base[MXN];
    void make_subtree(int node , int beg , int endd)
    {
       if(beg==endd)
       {
           subTree[node] = base[beg];
           return;
       }

       int left = node << 1;
       int mid = (beg+ endd) >> 1;

       make_subtree(left , beg , mid);
       make_subtree(left+1 , mid+1 , endd);

       subTree[node] = max( subTree[left] , subTree[left+1]);
       return;
    }
    int query_subtree(int node , int beg , int endd , int i , int j)
    {
        if(i > j)
            return -1;
        if(beg==i && endd==j)
        {
            return subTree[node];
        }

        int left = node << 1;
        int mid = (beg + endd) >> 1;

        int l =  query_subtree(left , beg , mid , i , min(j , mid));
        int r = query_subtree(left+1 , mid+1 , endd , max(i , mid+1) , j );

        return max(l , r);
    }
} tree[4*MXN];
void merge_tree(int node , int left , int right)
{
    for(int i = 1; i <= n ; i++)
    {
        tree[node].base[i] = max(tree[left].base[i], tree[right].base[i]);
    }
    tree[node].make_subtree(1 , 1 , n);
    return;
}
void make_tree(int node , int beg , int endd)
{
    if(beg==endd)
    {
        for(int i = 1; i <= n ; i++)
            tree[node].base[i] = ar[beg][i];
        tree[node].make_subtree(1 , 1 , n);
        return;
    }

    int left = node<<1;
    int mid = (beg+ endd) >> 1;

    make_tree(left, beg , mid);
    make_tree(left+1 , mid+1 , endd);
    merge_tree(node , left , left+1);
    return;
}
int query_tree(int node , int beg , int endd, int ri , int rj , int ci , int cj)
{
    if(ri > rj)
        return -1;
    if(beg == ri && endd== rj)
    {
        return tree[node].query_subtree(1 , 1 , n , ci , cj);
    }

    int left = node << 1;
    int mid = (beg + endd) >> 1;

    int l = query_tree(left , beg , mid , ri , min(rj , mid) , ci , cj);
    int r = query_tree(left+1 , mid+1 , endd , max(ri , mid+1) , rj, ci , cj);
    return max(l , r);
}
int main()
{
    int tc;
    scanf("%d",&tc);
    int cs = 0;
    while(tc--)
    {
        cs++;
        scanf("%d %d",&n , &m);
        for(int i = 1; i <= n ; i++)
        {
            for(int j = 1; j <= n ; j++)
            {
                scanf("%d",&ar[i][j]);
            }
        }
        make_tree(1 , 1 , n);
        int x ,y , s;
        printf("Case %d:\n",cs);
        for(int i = 0; i < m ; i++)
        {
            scanf("%d %d %d",&x ,&y , &s);
            int res = query_tree(1 , 1 , n , x , x+s-1 , y , y+s-1);
            printf("%d\n", res);
        }

    }
    return 0;
}
