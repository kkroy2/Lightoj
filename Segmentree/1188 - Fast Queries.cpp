#include<bits/stdc++.h>

using namespace std;
const int MXN = 100001;
set < int > tree[4*MXN] , res;
vector<int > ar;
set<int> Merge( set<int> a , set<int> b)
{
    set<int> ret;
    ret.insert(a.begin() , a.end());
    ret.insert(b.begin() , b.end());
    a.clear();
    b.clear();
    return ret;
}
void init(int node , int beg , int endd)
{
    //cout<<beg<<" "<<endd<<endl;
    if(beg==endd)
    {
        tree[node].insert(ar[beg]);
        return;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;

    init(left , beg , mid);
    init(right, mid+1 , endd);
    // merge(tree[left].begin(), tree[left].end(), tree[right].begin(), tree[right].end() , back_inserter(tree[node]));
    tree[node] = Merge(tree[left], tree[right]);
    //cout<<tree[node].size()<<" "<<tree[left].size()<<" "<<tree[right].size()<<" out "<<beg<<" "<<mid<<" "<<endd<<endl;
    return;
}
set<int> query(int node , int beg , int endd , int i , int j)
{
    //cout<<"in: "<<beg<<" "<<endd<<" "<<i<<" "<<j<<endl;
    if(i > j)
    {
        set<int>ret;
        return ret;
    }
    if(beg==i && endd==j)
    {
        //cout<<i<<" "<<j<<" mid "<<tree[node].size()<<" "<<node<<endl;
//        set<int>:: iterator it = tree[node].begin();
//           while(it!=tree[node].end())
//            {
//               cout<<*it<<endl;
//               it++;
//            }
        return tree[node];
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;
    //merge(l.begin() , l.end() , r.begin() , r.end() , back_inserter(ret));
    // cout<<l.size()<<" "<<r.size()<<" "<<"out"<<endl;
    return Merge( query(left , beg, mid , i , min(j , mid)),query(right , mid+1 , endd, max( i, mid+1) , j));

}
int main()
{
    int tc, cs=0,x, y, n, q;
    scanf("%d",&tc);
    while(tc--)
    {
        cs++;
        printf("Case %d:\n",cs);
        scanf("%d %d",&n,&q);
        ar.assign(n+1 , -1);
        for(int i = 1 ; i <= n ; i++)
            scanf("%d",&ar[i]);
        init(1 , 1, n);
//        for(int i = 1; i <= 2*n - 1; i++)
//        {
//            cout<<i<<" "<<tree[i].size()<<endl;
//        }
        for(int i = 0; i < q ; i++)
        {
            scanf("%d%d",&x,&y);
            res = query( 1, 1, n , x, y);
//            set<int>:: iterator it = res.begin();
//           while(it!=res.end())
//            {
//               cout<<*it<<endl;
//               it++;
//            }
            printf("%d\n", (int)res.size());
        }
        memset(tree, 0 ,sizeof(tree));
        res.clear();
        ar.clear();
    }
    return 0;
}
