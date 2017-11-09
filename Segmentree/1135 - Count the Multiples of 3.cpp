#include<bits/stdc++.h>
using namespace std;
const int MXN = 100001;
struct data
{
    int one , two ,zero, propV;
    bool propBool;
    data()
    {
        one = 0;
        two = 0;
        zero = 0;
        propV = 0;
        propBool = false;
    }
} tree[4*MXN];
void init(int node , int beg ,int endd)
{
    if(beg==endd)
    {
        tree[node].zero = 1;
        return;
    }
    int left = node<<1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;
    init(left , beg , mid);
    init(right , mid+1 ,endd);
    tree[node].zero = tree[left].zero + tree[right].zero;
    tree[node].one = 0;
    tree[node].two = 0;
    tree[node].propV = 0;
    tree[node].propBool = false;
    return;
}
data Merge(data a ,data b)
{
    data ret;
    ret.one = a.one + b.one;
    ret.two = b.two + a.two;
    ret.zero = a.zero + b.zero;
    ret.propV = 0;
    ret.propBool = false;
    return ret;
}
void updatechild(int node , int left , int right , int beg , int mid , int endd)
{
    tree[node].propV %=3;
    tree[left].propV +=tree[node].propV;
    tree[right].propV +=tree[node].propV;
    if(tree[node].propV == 1)
    {
        int tmp = tree[left].one;
        tree[left].one = tree[left].zero;
        tree[left].zero = tree[left].two;
        tree[left].two = tmp;
        tmp = tree[right].one;
        tree[right].one = tree[right].zero;
        tree[right].zero = tree[right].two;
        tree[right].two = tmp;
    }
    else if(tree[node].propV==2)
    {
        int tmp = tree[left].zero;
        tree[left].zero = tree[left].one;
        tree[left].one = tree[left].two;
        tree[left].two = tmp;
        tmp = tree[right].zero;
        tree[right].zero = tree[right].one;
        tree[right].one = tree[right].two;
        tree[right].two = tmp;
    }
    tree[node].propV = 0;
    tree[node].propBool = false;
    tree[left].propBool = true;
    tree[right].propBool = true;
    tree[left].propV %= 3;
    tree[right].propV %= 3;
    //cout<<tree[left].zero<<" "<<tree[right].zero<<" "<<beg<<" "<<mid<<" "<<endd<<" child"<<endl;
    return;
}
void update(int node , int beg, int endd , int i , int j)
{
   // cout<<"up in "<<beg<<" "<<endd<<" "<<i<<" "<<j<<endl;
    if(i > j)
        return;
    if(beg==i && endd == j)
    {
        tree[node].propV++;
        tree[node].propV %=3;
        tree[node].propBool = true;
        swap(tree[node].zero ,tree[node].one );
        swap(tree[node].zero , tree[node].two);
        return;
    }
    int left = node<<1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;

    if(tree[node].propBool && tree[node].propV)
    {
        updatechild(node , left , right , beg , mid , endd);
    }
    update(left , beg , mid , i , min(j , mid));
    update(right , mid+1 , endd , max(mid+1 , i) , j);

    tree[node] = Merge(tree[left] , tree[right]);
    //cout<<"up out "<<beg<<" "<<endd<<" "<<tree[node].zero<<" "<<tree[node].one<<" "<<tree[node].two<<endl;
    return;
}
int query(int node , int beg , int endd , int i , int j)
{
    //cout<<node<<" "<<beg<<" "<<endd<<" "<<i<<" "<<j<<endl;
    if(i > j)
        return 0;
    if(beg==i && endd == j)
    {
        //cout<<i<<" "<<j<<" "<<tree[node].zero<<endl;
        return tree[node].zero;
    }
    int left = node<<1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;
    if(tree[node].propBool&&tree[node].propV)
    {
        updatechild(node , left , right , beg , mid , endd);
    }
    int l = query(left , beg , mid , i , min(j , mid));
    int r = query(right , mid+1 , endd , max(mid+1 ,i) , j);
    //cout<<l<<" "<<r<<" out "<<beg<<" "<<endd<<" "<<mid<<" "<<i<<" "<<j<<endl;
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
        cin>>n>>q;
        init(1 , 1, n);
        for(int i = 0; i < q; i++)
        {
            int c , a , b;
            scanf("%d%d%d", &c, &a, &b);
            if(c==0)
            {
                update(1 , 1 , n , a+1, b+1);
            }
            else
            {
                int res = query(1, 1, n, a+1, b+1);
                printf("%d\n",res);
            }
        }
        memset(tree , 0 ,sizeof(tree));
    }
    return 0;
}

