#include<bits/stdc++.h>
using namespace std;

const int MXN = 100000;
int ar[MXN+5] ,n;
int tree[7*MXN + 5];

void init(int node , int beg , int endd)
{
    if(beg == endd)
    {
        tree[node] = ar[beg];
        return ;
    }
    int left = node*2;
    int right = node*2 + 1;
    int mid = (beg + endd)/2;

    init(left , beg , mid);
    init(right, mid+1 , endd);

    tree[node] = tree[right] + tree[left];
}
int update1(int node , int beg , int endd , int x)
{
    if(beg==x && endd==x)
    {
        int ret = tree[node];
        tree[node] = 0;
        ar[node] = 0;
        return ret;
    }

    int left = node * 2;
    int right = node*2 + 1;
    int mid = (beg + endd)/2;
    int l ;
    if(x <= mid)
         l = update1(left , beg , mid , x );
    else
        l = update1(right, mid+1 , endd,x);
    tree[node] = tree[left] + tree[right];
    return l;
}
void update2(int node , int beg , int endd , int x , int val)
{
    if(beg==x && endd==x)
    {
        tree[node] +=val;
        ar[x] +=val;
        return;
    }

    int left = node * 2;
    int right = node*2 + 1;
    int mid = (beg + endd)/2;
    if(x <= mid)
        update2(left , beg , mid , x  , val);
    else
        update2(right, mid+1 , endd, x , val);

    tree[node] = tree[left] + tree[right];
}
int query(int node , int beg , int endd , int x , int y)
{
    if(x > y)
        return 0;
    if(beg==x && endd == y)
    {
        return tree[node];
    }
    int left = node*2 ;
    int right = node*2 + 1;
    int mid = (beg + endd)/2;

    int l = query(left ,beg , mid, x , min(mid , y));
    int r = query(right , mid+1 , endd , max(mid+1 , x) , y);
    return r+l;
}

int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    //freopen("input.txt","r",stdin);
   // freopen("output.txt","w",stdout);
    while(tc--)
    {
        cs++;
        int q, I ,J;
        scanf("%d %d",&n,&q);
        for(int i = 1 ; i <= n ; i++)
        {
            scanf("%d" , &ar[i]);
        }
        init(1 , 1, n);
        printf("Case %d:\n",cs);
        int type;
        for(int i = 0; i < q ; i++)
        {
            scanf("%d",&type);
            if(type == 1)
            {
                scanf("%d", &I);
                int res = update1(1 , 1, n, I+1);
                printf("%d\n", res);
            }
            else if(type==2)
            {
                scanf("%d %d", &I,&J);
                update2(1 , 1, n, I+1, J);
            }
            else
            {
                scanf("%d %d", &I , &J);
                int res = query(1 ,1 , n,I+1, J+1);
                printf("%d\n", res);
            }
        }
    }
    return 0;
}

