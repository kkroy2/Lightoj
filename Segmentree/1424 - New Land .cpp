#include<bits/stdc++.h>
using namespace std;
int n , m;
const int mxn = 2*1e3 + 2;
int ar[mxn][mxn];
bool s[mxn][mxn];
typedef long long ll;
struct data
{
    int idx , val;
} tree[4*mxn];
void build(int row , int node , int beg , int endd)
{
    if(beg == endd)
    {
        tree[node].val = ar[row][beg];
        tree[node].idx = beg;
        return;
    }
    int left = node << 1;
    int right = left+1;
    int mid = (beg + endd) >> 1;
 
    build(row, left , beg , mid);
    build(row, right , mid+1, endd);
    tree[node].val = min(tree[left].val , tree[right].val);
    if(tree[node].val == tree[left].val)
    {
        tree[node].idx = tree[left].idx;
    }
    else
    {
        tree[node].idx = tree[right].idx;
    }
    return ;
}
data query(int row , int node , int beg , int endd , int l , int r)
{
    if(l > r)
    {
    data ret;
    ret.val = INT_MAX;
    ret.idx = -1;  
    return ret;
    }
    if(beg==l && endd == r)
    {
        return tree[node];
    }
    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;
 
    data lr = query(row , left , beg , mid , l , min(r , mid));
    data rr = query(row , right , mid+1 , endd , max(mid+1 , l) , r);
    data ret;
    ret.val = min(lr.val , rr.val);
    if(ret.val == lr.val)
    {
        ret.idx = lr.idx;
    }
    else
    {
        ret.idx = rr.idx;
    }
    return ret;
}
void preprocess()
{
    int cnt = 0;
    for(int i = 0; i < m; i++)
    {
        cnt  =0;
        for(int j = 0; j < n; j++)
        {
            if(s[j][i]==0)
            {
                cnt ++;
            }
            else
            {
                cnt = 0;
            }
            ar[j][i] = cnt;
        }
    }
}
ll solve(int row , int left , int right)
{
    if(left > right)
    return 0;
    data mn = query(row ,1 , 0 , m-1 , left , right);
    ll lr = solve(row , left , mn.idx-1);
    ll rr = solve(row, mn.idx+1 , right);
    ll ret = ar[row][mn.idx]*(right - left + 1);
    return max(ret , max(lr , rr));
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        cin>>n>>m;
        string st;
        for(int i = 0; i < n; i++)
        {
            cin>>st;
            for(int j = 0; j < m; j++)
            {
                s[i][j] = (bool) ((st[j]-'0') == 1);
            }
        }
    preprocess();
    ll ans = 0;
    for(int i = 0; i < n; i++)
    {
        build(i , 1 , 0 , m-1);
        ll ret = solve(i , 0 , m-1);
        ans = max(ret , ans);
    }
    cout<<"Case "<<cs<<": "<<ans<<endl;
    memset(s , 0 ,sizeof(s));
    memset(ar , 0 , sizeof ar);
}
    return 0;
}
