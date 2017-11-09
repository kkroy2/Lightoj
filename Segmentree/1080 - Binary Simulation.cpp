#include<bits/stdc++.h>
using namespace std;

const int MXN = 1000000;
int ar[MXN+3] ,n;
struct data
{
    int val;
    int pB = 0;

} tree[4*MXN + 5];
void updateNode(int node , int left ,int right)
{
    tree[left].pB ++;
    tree[right].pB ++;
    tree[right].pB %=2;
    tree[left].pB %=2;
    tree[node].pB = 0;
    return ;
}
void init(int node , int beg , int endd)
{
    if(beg ==  endd)
    {
        tree[node].val = ar[beg];
        return ;
    }
    int left = node*2;
    int right = node*2 + 1;
    int mid = (beg + endd)/2;

    init(left , beg , mid);
    init(right, mid+1 , endd);
    return;
}
void update( int node , int beg , int endd , int x , int y)
{
    if(x > y)
        return ;
    if(beg == x && endd == y)
    {
        tree[node].pB++;
        tree[node].pB %=2;
        return;
    }
    int left = node*2;
    int right = node*2 + 1;
    int  mid = (beg + endd)/2;

    if(tree[node].pB == 1)
        updateNode(node , left , right);

    update(left , beg , mid , x , min(mid , y) );
    update(right ,mid+1 , endd , max(mid+1 , x) , y);
    return ;
}

int query(int node , int beg , int endd , int x )
{
    if(beg==x && endd == x)
    {
        if(tree[node].pB == 1 )
        {
            tree[node].val = 1 - tree[node].val;
            tree[node].pB = 0;
        }
        //tree[node].pB %= 2;
        return tree[node].val;
    }
    int left = node*2 ;
    int right = left + 1;
    int mid = (beg + endd)/2;
    if(tree[node].pB == 1)
    {
        updateNode(node , left , right);
    }
    if(x<=mid)
        return query(left ,beg , mid, x);
    else
        return  query(right , mid+1 ,endd , x);
}

int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        string str;
        cin>>str;
        n =(int ) str.size();
        int q, I ,J;
        for(int i = 1 ; i <= n ; i++)
        {
            ar[i] = str[i-1] - '0';
        }
        scanf(" %d",&q);
        init(1 , 1, n);
        char ch;
        printf("Case %d:\n",cs);
        for(int i = 0; i < q ; i++)
        {
            scanf(" %c", &ch);
            if(ch=='I')
            {
                scanf(" %d %d", &I , &J);
                update(1 , 1 , n , I , J);
            }
            else
            {
                scanf(" %d", &I);
                int res = query(1 ,1 , n, I);
                printf("%d\n", res);
            }
        }
        str.clear();
    }
    return 0;
}

