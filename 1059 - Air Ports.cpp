#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
struct Edge
{
    ll w , v, u;
} e;

ll parent[200000];
vector< Edge > vt;
ll n , m , A;
bool operator < ( Edge a , Edge b)
{
    return a.w<b.w;
}
ll find_parent( ll x)
{
    if(parent[x] == x)
        return parent[x];
    return parent[x] = find_parent( parent[x]);
}
ll  mn =0;
void krs()
{
    sort(vt.begin() , vt.end());
    for(int i =0; i <= n ; i++)
    {
        parent[i]  = i;
    }
    int sz = vt.size();
    for(int i = 0; i < sz ; i++)
    {
      //  cout<<vt[i].w<<" "<<A<<endl;
        if(find_parent(vt[i].u) != find_parent(vt[i].v) && (vt[i].w < A))
        {
            mn += vt[i].w;
         //   cout<<mn<<" "<<vt[i].u << " " <<vt[i].v<<endl;
            parent[parent[vt[i].u]] = parent[vt[i].v] ;
        }
    }
}

int main()
{
    int tc;
    cin>>tc;
    int cs = 0 , x, y , c;
    while(tc--)
    {
        cs++;
        //cin>>n>>m>>A;
        scanf("%lld %lld %lld", &n,  &m , &A);
        for(int i =0; i < m ; i++)
        {
            //cin>>x>>y>>c;
            scanf("%d %d %d", &x , &y , &c);
            e.u = x;
            e.v = y;
            e.w  = c;
            vt.push_back(e);
        }
        krs();
        set<int>s;
        for(int i = 1 ; i <= n ; i++)
        {
            s.insert( find_parent(i));
        }
        ll res  = (long long ) s.size();
        //cout<<mn<<endl;
        //cout<<"Case "<<cs<<": "<<mn+(res*A)<<" "<<res<<endl;
        printf("Case %d: %lld %lld\n", cs , mn + (res*A) , res);
        vt.clear();
        mn = 0;
        s.clear();

    }
    return 0;
}
