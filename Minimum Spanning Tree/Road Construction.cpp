#include<bits/stdc++.h>
using namespace std;
struct Edge
{
    int u , v;
    int cost;
};
vector< Edge > E;
bool operator<( Edge a , Edge b)
{
    return a.cost < b.cost;
}
int parent[303], n;
int find_parent(int x)
{
    if(parent[x]==x)
        return x;
    return parent[x] = find_parent(parent[x]);
}
int kruskal(int n)
{
    for(int i = 1 ; i <= n ; i++)
        parent[i] = i;
    sort(E.begin() , E.end());
    int sz = E.size();
    int ans = 0;
    for(int i = 0 ; i < sz ; i++)
    {
        if(find_parent(E[i].u)!=find_parent(E[i].v))
        {
            parent[parent[E[i].u]] = parent[E[i].v];
            ans +=E[i].cost;
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
        int value = 0;
        cs++;
        cin>>n;
        string u , v;
        Edge e;
        int cost;
        map< string , int > mp;
        for(int  i = 0 ; i < n ; i++)
        {
            cin>>u>>v>>cost;
            if(!mp[u])
            {
                mp[u] = ++value;
            }
            if(!mp[v])
            {
                mp[v] = ++value;
            }
            e.u = mp[u];
            e.v = mp[v];
            e.cost = cost;
            E.push_back(e);
        }
        //cout<<value<<endl;
        int res = kruskal(value);
        set< int > s;
        for(int i= 1 ; i <= value ; i++)
        {
            s.insert(find_parent(i));
        }
        if(s.size()==1)
            cout<<"Case "<<cs<<": "<<res<<endl;
        else
            cout<<"Case "<<cs<<": Impossible"<<endl;
      E.clear();
      mp.clear();
      s.clear();
      memset(parent , 0 , sizeof(parent));
    }
    return 0;
}
