#include<bits/stdc++.h>
using namespace std;
const int mxn = 7*1e4 + 10;
struct input
{
    long long x1 , y1 , y2;
    int open;
    input(long long _x1 , long long _y1 , long long _y2 ,int _open)
    {
        x1 = _x1;
        y1 = _y1;
        y2 = _y2;
        open = _open;
    }
    bool operator<(const input &in) const{
   
        return x1 < in.x1;
    }
};
vector< input > ar;
long long actual[mxn];
long long s[mxn+10];
vector< long long > idx;
int n , k;
map< long long , int > mp;
struct data
{
    int cp;
    long long sum;
    long long rangeSum;
}tree[4*mxn];
 
 
void update(int node , int beg , int endd, int l , int r , int val)
{
    if(idx[endd] < l || idx[beg] > r)
    return;
    int left = node << 1;
    int right = left + 1;
    int mid = ( beg + endd) >> 1;
    if(idx[beg] >= l && idx[endd] <=r)
    {
        tree[node].cp +=val;
        if( tree[node].cp)
        {
            tree[node].sum = idx[endd] - idx[beg];
        }
        else
        {
            tree[node].sum = tree[left].sum + tree[right].sum;
        }
        return;
    }
    if(beg+ 1 >= endd)
    return;
    update(left, beg , mid , l ,r , val );
    update(right , mid , endd , l , r , val);
    if(tree[node].cp)
    {
        tree[node].sum = idx[endd] - idx[beg];
    }
    else
    {
        tree[node].sum = tree[left].sum + tree[right].sum;
    }
    return;
}
int main()
{
   
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        memset(tree , 0 , sizeof tree);
        cs++;
        cin>>n;
        long long x1 , x2 , y1 , y2;
        int yc =0;
        for(int i = 1; i <= n; i++)
        {
            cin>>x1>>y1>>x2>>y2;
            ar.push_back( input(x1 , y1 , y2 , 1));
            ar.push_back( input(x2 , y1 , y2 , -1));
            s[yc++] = y1;
            s[yc++] = y2;
        }
        sort(s , s+yc);
        idx.push_back(s[0]);
        for(int i = 1;i < yc; i++)
        {
            if(idx[idx.size()-1] != s[i])
            idx.push_back(s[i]);
        }
       
        sort(ar.begin(), ar.end());
        long long ans = 0;
        update(1 , 0 , idx.size()-1 , ar[0].y1 , ar[0].y2, ar[0].open);
        for(int i = 1; i < ar.size(); i++)
        {
            ans += (long long)(ar[i].x1 - ar[i-1].x1)*(long long)tree[1].sum;
            update(1 , 0 , idx.size()-1 , ar[i].y1, ar[i].y2, ar[i].open );
        }
        cout<<"Case "<<cs<<": "<<ans<<endl;
        ar.clear();
        idx.clear();
        mp.clear();
        memset(actual, 0 , sizeof actual);
    }
    return 0;
}
