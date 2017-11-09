#include<bits/stdc++.h>
using namespace std;
const int mxn = 10003;
int n, m;
vector< int > adj[mxn] , bcc[mxn] ;
int dfs_low[mxn] , dfs_num[mxn] , dfsnum , bccnum , el, root , rcnt;
bool vis[mxn];
map< pair< int , int > , int > mp;
map< int  , int> ap;
void dfs(int u , int parent)
{
	dfs_low[u] = dfs_num[u] = dfsnum++;
	vis[u] = true;
	for(int i = 0; i < (int) adj[u].size(); i++)
	{
		int v = adj[u][i];
		if(!vis[v])
		{
			dfs(v , u);
			if(dfs_low[v] > dfs_num[u])
			{
			//	cout<<v<<" bridge "<<u<<endl;
				mp[make_pair(min(v , u) , max(u , v))]=1;
				
			}
			dfs_low[u] = min(dfs_low[u] , dfs_low[v]);
		}
		else if(vis[v] && parent!=v)
		{
			dfs_low[u] = min(dfs_low[u] , dfs_num[v]);
		}
	}
}
void dfs2(int u)
{
	vis[u] = true;
	for(int i =0; i < (int) adj[u].size(); i++)
	{
		int v = adj[u][i];
		if(mp[make_pair(min(u , v) , max(u , v))])
		continue;
		if(!vis[v])
		{
			dfs2(v);
		}
	}
	bcc[bccnum].push_back(u);
}
int color[mxn] , flag = false;
void dfs3(int u)
{
	for(int i = 0; i < (int)adj[u].size(); i++)
	{
		
		int v = adj[u][i];
		if(mp[make_pair(min(u , v) ,max(u , v))])
		continue;
		if(color[v]!=-1)
		{
			if(color[v] == color[u])
			flag = true;
		}
		else
		{
		color[v] = 1 - color[u];
		dfs3(v);
	}
	}
}

int main()
{
	int tc;
	scanf("%d" , &tc);
	int cs = 0;
	while(tc--)
	{
		cs++;
		scanf("%d %d" , &n , &m);
		int u , v;
		
		for(int i = 0; i < m ; i++)
		{
			scanf("%d %d" , &u , &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		memset(vis , false , sizeof(vis));
		dfsnum =0;
		for(int i = 0; i < n ; i++)
		{
			if(!vis[i])
			{
				root = i;
				rcnt = 0;
				dfs(i , -1);
				if(rcnt==1)
				ap[root] = 1;
			}
		}
		memset(dfs_num , 0 , sizeof(dfs_num));
		memset(dfs_low ,0 , sizeof(dfs_low));
		memset(vis , false, sizeof(vis));
		bccnum = 0;
		memset(bcc , 0 , sizeof(bcc));
		for(int i = 0; i < n ; i++)
		{
			if(!vis[i])
			{
				
				bccnum++;
		//		cout<<i<<" bccnum "<<bccnum<<endl;
				dfs2(i);
			}
		}
		int res = 0;
		memset(vis  , false ,sizeof(vis));
		memset(color ,-1 , sizeof(color));
		for(int i = 1; i <= bccnum; i++)
		{
			
			flag = false;
			color[bcc[i][0]] = 0;
			dfs3(bcc[i][0]);
			if(flag)
			res += (int) bcc[i].size();
		}
		printf("Case %d: %d\n" ,cs , res);
		for(int i =0; i < mxn ; i++)
		{
			adj[i].clear();
			bcc[i].clear();
		}
		mp.clear();
		ap.clear();
	}
	
	return 0;
}
