#include<bits/stdc++.h>
using namespace std;

struct Edge
{
    int v, u, w;
};
vector < Edge > E;
bool operator< ( Edge a , Edge b)
{
    return a.w < b.w;
}

int parent[303] , n;

int find_parent(int x)
{
    if(parent[x]==x)
        return parent[x];
    return parent[x] = find_parent(parent[x]);
}
int gcd( int a , int b)
{
    if(b==0)
        return a;
    return ( b , a%b);
}
int kruskal(int n)
{
     for(int i = 0 ; i <= n; i++)
            parent[i] = i;
    int sz = E.size();
    int ans = 0 , cnt = 0;
    for(int i = 0; i < sz ; i++)
    {
        if(find_parent(E[i].u) != find_parent(E[i].v))
        {
          //  cout<<"loop"<<endl;
            parent[parent[E[i].u]] = parent[E[i].v];
           //parent[parent[E[i].v]] = parent[E[i].u];
            //parent[E[i].v] = parent[E[i].u];
            ans += E[i].w;
            cout<<ans<<endl;
            cout<<parent[E[i].u]<<" "<<parent[E[i].v]<<" "<<E[i].v<<" "<<E[i].u<<endl;
        }
    }
    return ans;
}

int main()
{
   int tc;
   cin>>tc;
   int cs = 0;
   while(tc--)
   {
       cs++;
       cin>>n;
       int u , v, w;
       Edge e;
       while(cin>>u>>v>>w&&(u||v||w))
       {
           e.u = u;
           e.v = v;
           e.w = w;
           E.push_back(e);
       }
      sort(E.begin(), E.end());
      //for(int i = 0 ; i < E.size() ; i++)
       // cout<<E[i].w<<endl;
     int res1 = kruskal(n);
     //cout<<res1<<endl;
     reverse(E.begin() , E.end());
     int res2 = kruskal(n);
     //cout<<res2<<endl;
     int res = res1 + res2;
     //cout<<res<<endl;
     if(res%2==1)
        cout<<"Case "<<cs<<": "<<res<<"/2"<<endl;
       else
       cout<<"Case "<<cs<<": "<<res/2<<endl;
     E.clear();
   }
    return 0;
}
