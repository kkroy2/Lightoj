#include<bits/stdc++.h>
using namespace std;

const int MXN = 100005;

struct data
{
  long long int sum , propV;
  bool propBool;
  data()
  {
      propBool = false;
      propV = 0;
      sum = 0;
  }
}tree[4*MXN + 5];
void updatechild(int node , int left, int right , int beg ,int mid , int endd)
{
    tree[left].sum = (mid - beg +1)*tree[node].propV;
    tree[right].sum = (endd - mid)*tree[node].propV;
    tree[left].propV = tree[node].propV;
    tree[right].propV = tree[node].propV;
    tree[left].propBool = true;
    tree[right].propBool = true;
    tree[node].propBool = false;
    tree[node].propV = 0;
    return;
}
data Merge(data l , data r)
{
    data ret;
    ret.sum = l.sum + r.sum;
    ret.propV = 0;
    ret.propBool = false;
    return ret;
}
void update(int node , int beg , int endd , int i , int j , int val)
{
    if(i > j)
        return;
    if(beg==i&&endd ==j)
    {
        //cout<<(endd - beg + 1)*val<<" "<<beg<<" "<<endd<<endl;
        tree[node].sum = (endd - beg + 1)*val;
        tree[node].propBool = true;
        tree[node].propV = val;
        return;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;

    if(tree[node].propBool)
    {
        updatechild(node , left, right, beg, mid , endd);
    }
    update(left , beg , mid , i , min( j , mid), val);
    update(right , mid+1 , endd , max(i , mid+1) , j, val);
    tree[node] = Merge(tree[left] , tree[right]);
    return;
}
long long int query( int node , int beg , int endd , int i , int j)
{
    if(i > j)
        return 0;
    if(beg==i &&endd==j)
    {
        return tree[node].sum;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;
    if(tree[node].propBool)
    {
        updatechild(node , left, right, beg, mid , endd);
    }
    long long int l = query( left , beg , mid , i , min(mid , j));
    long long int r = query( right , mid+1 , endd , max(mid+1 , i) , j);
   // cout<<"out "<<l<<" "<<r<<" "<<beg<<" "<<mid<<" "<<endd<<endl;
    return l+r;
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
        int n, q;
        scanf("%d%d",&n ,&q);
        for(int i = 0; i< q; i++)
        {
            int c , x, y, z;
            scanf("%d",&c);
            if(c==1)
            {
                scanf("%d %d %d",&x, &y , &z);
                update(1 , 1, n, x+1 , y+1 , z);
            }
            else
            {
                scanf("%d %d",&x ,&y);
                long long int res = query( 1, 1, n, x+1 , y+1);
               // cout<<res<<endl;
                long long int gcd = __gcd(res , (long long int)y-x+1);
                long long int p = res/gcd;
                long long int q = (y-x+1)/gcd;
                if(q==1)
                {
                    printf("%lld\n",p);
                }
                else
                {
                    printf("%lld/%lld\n",p,q);
                }
            }
        }
        memset(tree, 0 ,sizeof(tree));

    }
    return 0;
}
