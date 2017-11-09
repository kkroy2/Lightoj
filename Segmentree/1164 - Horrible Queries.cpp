#include<bits/stdc++.h>

using namespace std;

const int MXN = 100001;
struct data
{
    long long int sum , prop;
    bool flag;
} tree[5*MXN + 5];

void updatechild(long long node ,long long beg , long long endd, long long mid , long long left , long long right)
{
    //cout<<"child in: "<<node<<" "<<tree[node].prop<<" "<<tree[node].sum<<" "<<tree[node].flag<<" "<<beg<<" "<<endd<<" "<<mid<<" "<<left<<" "<<right<<endl;
    tree[left].prop += tree[node].prop;
    tree[right].prop += tree[node].prop;
    tree[left].sum += (mid - beg + 1)*tree[node].prop;
    tree[right].sum += ( endd - mid)*tree[node].prop;
    tree[right].flag =true ;
    tree[left].flag = true;
    tree[node].flag = false;
    tree[node].prop = 0;
    //cout<<"child out: "<<tree[node].sum<<" "<<tree[left].sum<< " "<<tree[right].sum<<" "<<endl;
   // cout<<" child flag: "<<tree[left].flag<<" "<<tree[right].flag<<endl;
    //cout<<" child prop: "<<tree[left].prop<<" "<<tree[right].prop<<endl;
    return;
}
data Merge( data l , data r)
{
    data ret ;
    ret.sum = l.sum + r.sum;
    ret.flag = false;
    ret.prop = 0;
    return ret;
}
void update(long long node , long long beg , long long endd , long long i , long long j , long long val)
{
    //cout<<"in :"<<node <<" "<<tree[node].sum<<endl;
    //cout<<"up: "<<node<<" "<<beg<<" "<<endd<<" "<<i<<" "<<j<<" "<<val<<endl;
    if(i>j || beg > endd)
        return;
    if(beg == i &&endd == j)
    {
        tree[node].prop += val;
        tree[node].sum += (endd - beg + 1)*val;
        tree[node].flag = true;
      //  cout<<tree[node].sum<<" "<<node<<endl;
        return;
    }
    long long left = node << 1;
    long long right = left + 1;
    long long mid = (beg + endd) >> 1;
//cout<<"HOW"<<endl;
//cout<<"flag value : "<<tree[node].flag<< "node: "<<node <<endl;
    if(tree[node].flag == true)
    {
        updatechild(node , beg , endd , mid , left , right);
    }

    update(left , beg , mid , i , min(j , mid), val);
    update(right , mid+1, endd , max(i, mid+1), j, val);

    tree[node] = Merge(tree[left] , tree[right]);
   // cout<<"out "<<node << " "<<tree[node].sum<<endl;
    return;
}
data query(long long node , long long beg , long long endd , long long i , long long j)
{
  // cout<<"in: "<<node <<" "<<beg<<" "<<endd<<" "<<i<<" "<<j<<" "<<tree[node].sum<<endl;
    if( i > j)
    {
        data ret ;
        ret.sum = 0;
        ret.prop = 0;
        ret.flag = false;
        return ret;
    }
    if(beg == i && endd == j)
        {
      //  cout<<i<<" "<<j<<" "<<node<<" "<<tree[node].sum<<endl;
            return tree[node];
        }

    long long left = node << 1;
    long long right = left + 1;
    long long mid = (beg + endd) >> 1;

    if(tree[node].flag == true)
    {
        updatechild( node , beg , endd , mid , left , right);
    }

    data l = query( left , beg , mid , i , min( mid , j));
    //cout<<"out " <<node<<endl;
    //cout<<l.sum << " " << beg << " "<<mid <<" "<<i << " " << j <<endl;
    data r = query( right , mid+1 , endd , max(mid+1 , i), j);
    //tree[node] = Merge( tree[left] , tree[right]);
    //cout<<tree[node].sum<<endl;
   // cout<<r.sum<<" "<<" "<<endd <<endl;
    data ans = Merge( l , r);
  // cout<<"Merge : "<<ans.sum<<endl;
    return ans;
}
int main()
{
    long long tc;
    cin>>tc;
    long long cs = 0;
    while(tc--)
    {
        cs++;
        memset(tree, 0 , sizeof(tree));
        long long n, q;
        cin>>n>>q;
        long long c, x, y, v;
        printf("Case %lld:\n",cs);
        for(long long i = 0; i < q ; i++)
        {
            //cin>>c;
            scanf("%lld",&c);
            if(c==0)
            {
                //cin>>x>>y>>v;
                scanf("%lld %lld %lld",&x, &y, &v);
                update( 1 , 1 , n , x+1, y+1 , v);
            }
            else
            {
                //cin>>x>>y;
                scanf("%lld %lld",&x, &y);
                data res = query(1 , 1, n, x+1 , y+1 );
                //cout<<res.sum<<endl;
               // cout<<" OUT "<<endl;
                printf("%lld\n",res.sum);
            }
        }

    }
    return 0;
}
