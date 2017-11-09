#include<bits/stdc++.h>
using namespace std;
const int mxn = 10005;
vector< int > adj[mxn] , bcc[mxn];
int low[mxn] , dv[mxn], parent[mxn] , bccnt= 0 ,root, rootchild;
bool vis[mxn] , ap[mxn];
set< int > apcnt[mxn];
typedef unsigned long long ull;

int cnt ;
void dfs(int u)
{
	vis[u] = true;
	low[u] = dv[u] = cnt;
	cnt++;
	for(int i = 0; i < adj[u].size(); i++)
	{
		int v = adj[u][i];
		if(!vis[v])
		{
			if(root==u)
			rootchild++;
			parent[v] = u;
			dfs(v);
			if(low[v] >= dv[u] && root != u)
			{
				ap[u] = true;
			}
			low[u] = min(low[u] , low[v]);
		}
		else if(parent[u]!=v)
		{
			low[u] = min(low[u] , dv[v]);
		}
		
	}
}
void dfs1(int u)
{
	vis[u] = true;
	bcc[bccnt].push_back(u);
	for(int i = 0; i < adj[u].size(); i++)
	{
		int v = adj[u][i];
		if(ap[v])
		{
		apcnt[bccnt].insert(v);
		continue;
	   }
		if(!vis[v])
		{
			dfs1(v);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin>>tc;
	int cs = 0;
	while(tc--)
	{
		cs++;
		int n , m , u ,v;
		cin>>n>>m;
		for(int i = 0; i < m; i++)
		{
			cin>>u>>v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		memset(vis , false , sizeof(vis));
		memset(ap , false , sizeof(ap));

		for(int i = 0; i < n; i++)
		{
			if(!vis[i])
			{
				cnt = 0;
				root = i;
				rootchild = 0;
				dfs(i);
				if(rootchild > 1)
				ap[root] = true;
			}
		}
		
		memset( vis , false , sizeof(vis));
		bccnt = 0;
		for(int i = 0;  i < n ; i++)
		{
			if(ap[i])
			continue;
			if(!vis[i])
			{
				bccnt++;
				dfs1(i);
			}
		}
		
		if(bccnt==1)
		{
			if(bcc[1].size()==0)
			{
				cout<<"Case "<<cs<<": "<<0<<" "<<1<<endl;
			}
			else if(bcc[1].size()==1)
			{
				cout<<"Case "<<cs<<": "<<1<<" "<<1<<endl;
			}
			else
			{
				ull res = ( (unsigned long long) bcc[1].size()*((unsigned long long )bcc[1].size()-1))/2;
				cout<<"Case "<<cs<<": "<<2<<" "<<res<<endl;
			}
		}
		else
		{
			ull res =  1 , r=0;
			for(int i =1; i <= bccnt; i++)
			{
				if(apcnt[i].size() <= 1)
				res *= (unsigned long long )bcc[i].size();
				else
				r++;
			}
			cout<<"Case "<<cs<<": "<<bccnt-r<<" "<<res<<endl;
		}
		for(int i = 0; i < mxn; i++)
		{
			adj[i].clear();
			bcc[i].clear();
			apcnt[i].clear();
		}
	}
	return 0;
}
