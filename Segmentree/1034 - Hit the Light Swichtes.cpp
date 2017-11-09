#include<bits/stdc++.h>
using namespace std;
vector< int > adj[10005] ,TS;
int vis[10005];
void dfs(int u)
{
    if(vis[u]==1)
        return;
    vis[u]  = 1;
    for(int i = 0; i < adj[u].size(); i++)
    {
        dfs(adj[u][i]);
    }
    TS.push_back(u);
    return;
}
int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        int n , m;
        scanf("%d%d",&n , &m);
        int u , v;
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d",&u , &v);
            adj[u].push_back(v);
        }
        memset(vis , 0 , sizeof(vis));
        dfs(1);
        reverse(TS.begin() , TS.end());
        memset(vis , -1 , sizeof(vis));
        int cnt = 0;
        for(int i = 0; i < TS.size() ; i++)
        {
           if(vis[TS[i]]==-1)
           {
               cout<<TS[i]<<endl;
               cnt++;
               dfs(TS[i]);
           }
        }
        cout<<"Case "<<cs<<": "<<cnt<<endl;
        for(int i = 0; i < 10005; i++)
        {
            adj[i].clear();
        }
        TS.clear();
    }
    return 0;
}
