#include<bits/stdc++.h>
using namespace std;

const int MXN = 100000;
int ar[MXN+3] ,n;
int tree[4*MXN + 5];

void init(int node , int beg , int endd)
{
    if(beg==endd)
    {
        tree[node] = ar[beg];
        return ;
    }
    int left = node*2;
    int right = node*2 + 1;
    int mid = (beg + endd)/2;

    init(left , beg , mid);
    init(right, mid+1 , endd);

    tree[node] =min( tree[right] , tree[left]);
}

int query(int node , int beg , int endd , int x , int y)
{
    if(x > y)
        return INT_MAX;
    if(beg==x && endd == y)
    {
        return tree[node];
    }
    int left = node*2 ;
    int right = node*2 + 1;
    int mid = (beg + endd)/2;

    int l = query(left ,beg , mid, x , min(mid , y));
    int r = query(right , mid+1 , endd , max(mid+1 , x) , y);
    return min(r , l);
}

int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        int q, I ,J;
        scanf("%d %d",&n,&q);
        for(int i = 1 ; i <= n ; i++)
        {
            scanf("%d" , &ar[i]);
        }
        //cout<<ar[1]<<endl;
        init(1 , 1, n);
        //cout<<"Case "<<cs<<":"<<endl;
        printf("Case %d:\n",cs);
        for(int i = 0; i < q ; i++)
        {
            scanf("%d %d", &I , &J);
            int res = query(1 ,1 , n,I, J);
            printf("%d\n", res);
        }
    }
    return 0;
}
