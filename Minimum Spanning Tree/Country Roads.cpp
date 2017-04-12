#include<bits/stdc++.h>
using namespace std;
#define INF 999999999
typedef pair < int , int > PII;
vector < PII > adj[505];
vector< int > dist;
int n, m;
void DKTS(int src)
{
    priority_queue < pair< int , int > > PQ;
    dist[src] = 0;
    PQ.push(make_pair(dist[src] , src));
    while(!PQ.empty())
    {
        PII p;
        p = PQ.top();
        PQ.pop();
        for(int  i = 0; i < adj[p.second].size(); i++)
        {
            PII q = adj[p.second][i];
            if(dist[q.first] > max(q.second, dist[p.second]) )
            {
                dist[q.first]  =  max(q.second , dist[p.second]);
                PQ.push(make_pair(-dist[q.first] , q.first));
            }
        }
    }
}
int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        cin>>n>>m;
        dist.assign(n+1 , INF);
        for(int i = 0; i < m ; i++)
        {
            int x , y , w;
            cin>>x>>y>>w;
            adj[x].push_back(make_pair(y,w));
            adj[y].push_back(make_pair(x, w));
        }
        int t;
        cin>>t;
        DKTS(t);
        cout<<"Case "<<cs<<":"<<endl;
        for(int i = 0 ; i < n; i++)
        {
            if(dist[i]>=INF)
                cout<<"Impossible"<<endl;
            else
                cout<<dist[i]<<endl;
        }
        dist.clear();
        for(int i = 0 ; i < 505; i++)
            adj[i].clear();

    }
    return 0;
}
