#include<bits/stdc++.h>
using namespace std;
#define MXN 100005
#define mod 1000000007
int ar[MXN] , tmp[MXN];
long long tree[4*MXN];
void make_tree(int node , int beg , int endd)
{
    if(beg==endd)
    {
        tree[node] = 0;
        return;
    }

    int left = node << 1;
    int mid = (beg+endd) >> 1;

    make_tree(left , beg , mid);
    make_tree(left+1 , mid+1 ,endd);
    tree[node]  = tree[left] + tree[left+1];
    return;
}

long long int query(int node , int beg , int endd ,int i ,int j)
{
    if(i > j)
        return 0;
    if(beg==i && endd==j)
    {
        return tree[node];
    }

    int left = node << 1;
    int mid = (beg+ endd)>>1;

    return (query(left , beg , mid , i , min(j, mid)) + query(left+1, mid+1 , endd , max(i , mid+1) , j))%mod;
}

void update(int node , int beg , int endd , int pos , long long int val)
{
    if(beg==pos && endd ==pos)
    {
        tree[node] += val;
        return;
    }

    int left = node << 1;
    int mid = (beg + endd) >> 1;
    if(pos <= mid)
    update(left , beg , mid , pos , val);
    else
        update(left+1 , mid+1 , endd , pos , val);
    tree[node] = (tree[left] + tree[left+1])%mod;
    return;
}

int main()
{
    //freopen("output.txt","w" , stdout);
    int tc;
    scanf("%d",&tc);
    int cs = 0;
    while(tc--)
    {
        cs++;
        int n;
        long long ans = 0;
        scanf("%d",&n);
        for(int i = 0; i < n ; i++)
        {
            scanf("%d",&ar[i]);
            tmp[i] = ar[i];
        }
        sort(tmp , tmp+n);
        map< int , int > mp;
        int cnt = 1;
        for(int i = 0; i < n; i++ )
        {
            if(mp[tmp[i]] == 0)
            {
                mp[tmp[i]] = cnt++;
            }
        }
        int sz= cnt - 1;
//        cout<<sz<<endl;
//        for(int i  = 1; i < vp.size(); i++)
//            cout<<vp[i].first<<" "<<vp[i].second<<endl;
        make_tree(1 , 1 , sz );
        ans = 0;
        for(int i = 0; i < n ; i++)
        {
            int pos = mp[ar[i]];
            ans = (query(1 , 1 , sz , 1 , pos - 1 ) + 1)%mod;
            update(1 , 1 , sz , pos , ans );
        }
       // cout<<query(1 , 1, sz, 1 , sz)<<endl;
        printf("Case %d: %lld\n" , cs , tree[1]);
    }
    return 0;
}
