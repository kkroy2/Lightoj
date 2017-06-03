#include<bits/stdc++.h>
using namespace std;
#define MXN 100005
vector< int > adj[MXN];
int ar[MXN] , N;
int parent[MXN] , level[MXN] , subSize[MXN] , chainHead[MXN] , chainInd[MXN] , baseArray[MXN] , posInBaseArray[MXN];
int baseCount = -1,chainNo = 0;
int sparse[MXN][22];
int tree[6*MXN];
void dfs(int cur , int prev , int depth)
{
    parent[cur] = prev;
    level[cur] = depth;
    subSize[cur] = 1;
    int sz = adj[cur].size();
    for(int i= 0; i < sz ; i++)
    {
        if(adj[cur][i] != prev )
        {
            dfs(adj[cur][i] , cur , depth+1);
            subSize[cur] += subSize[adj[cur][i]];
        }
    }
}
void hld(int cur , int prev)
{
    if(chainHead[chainNo] == -1)
        chainHead[chainNo] = cur;
    chainInd[cur] = chainNo;
    baseArray[++baseCount] = ar[cur];
    posInBaseArray[cur] = baseCount;

    int sz = adj[cur].size();
    int ind = -1 , maxi = -1;
    for(int i = 0; i < sz ; i++)
    {
        if(subSize[adj[cur][i]] > maxi && prev != adj[cur][i])
        {
            ind = i;
            maxi = subSize[adj[cur][i]];
        }
    }

    if(ind >= 0)
    {
        hld( adj[cur][ind] , cur);
    }

    for(int i = 0; i < sz; i++)
    {
        if( i!= ind && adj[cur][i] != prev)
        {
            chainNo++;
            hld(adj[cur][i] , cur);
        }
    }
}
void lca_init()
{
    memset(sparse , -1 , sizeof(sparse));
    for(int i = 0; i < N ; i++)
        sparse[i][0] = parent[i];
    for(int j = 1; (1 << j) < N ;j++ )
    {
        for(int i = 0; i < N ; i++)
        {
            if(sparse[i][j-1]!=-1)
            sparse[i][j] = sparse[sparse[i][j-1]][j-1];
        }
    }
}
int lca_query(int p , int q)
{
    if(level[p] < level[q])
        swap(p , q);
    int log = 1;
    while(1)
    {
        if( (1 << log) > level[p])
        {
            break;
        }
        log++;
    }
    log -=1;

    for(int i = log ; i >= 0 ; i--)
    {
        if( (level[p] - (1 << i)) >= level[q])
        {
            p = sparse[p][i];
        }
    }
    if( p == q)
        return q;

    for(int i = log; i >= 0; i--)
    {
        if(sparse[p][i] !=-1 && sparse[p][i]!=sparse[q][i])
        {
            p = sparse[p][i];
            q = sparse[q][i];
        }
    }
    return parent[p];
}

void make_tree(int node , int beg , int endd)
{
    if(beg==endd)
    {
        tree[node] = baseArray[beg];
        return;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd) >> 1;

    make_tree(left , beg , mid);
    make_tree(right , mid+1 , endd);

    tree[node] = tree[left] + tree[right];

    return;
}

void update_tree(int node , int beg , int endd , int pos , int val)
{
    if(beg == pos && endd == pos)
    {
        baseArray[beg] = val;
        tree[node] = val;
        return;
    }

    int left = node << 1;
    int right = left + 1;
    int mid = (beg + endd ) >> 1;

    if( mid >= pos)
    {
        update_tree(left , beg , mid , pos , val);
    }
    else
    {
        update_tree(right , mid+1 , endd , pos , val);
    }
    tree[node] = tree[left] + tree[right];
    return;
}

int query_tree(int node , int beg , int endd , int i , int j)
{
   if(i > j)
        return 0;
   if(beg == i && endd == j)
   {
       return tree[node];
   }

   int left = node << 1;
   int right = left + 1;
   int mid = (beg + endd) >> 1;

   int l = query_tree(left , beg , mid , i ,min( mid , j));
   int r = query_tree(right , mid+1 , endd , max(i , mid+1 ) , j);
   return l+r;
}

int query_up(int u , int v)
{
    int ui = chainInd[u];
    int vi = chainInd[v];
    if(v == u)
        return baseArray[posInBaseArray[v]];
    if(ui == vi)
    {
        int up = posInBaseArray[u];
        int vp = posInBaseArray[v];
        if(up > vp)
            swap(up , vp);
        return query_tree(1 , 0 , baseCount , up , vp);
    }
    else
    {
        int vh = chainHead[vi];
        int res1  = query_up(u , parent[vh]);
        return res1 + query_tree(1 , 0 , baseCount , posInBaseArray[vh] , posInBaseArray[v]);
    }
}
int query(int u , int v)
{
    int LCA = lca_query(u , v);
    int res1 = query_up(LCA , u);
    int res2 = query_up( LCA , v);
    return res1 + res2 - baseArray[posInBaseArray[LCA]];
}
void change(int pos , int val)
{
    int pi = posInBaseArray[pos];
    update_tree(1 , 0 , baseCount , pi , val);
    return;
}
int main()
{
    int tc;
    scanf("%d",&tc);
    int cs = 0;
    while(tc--)
    {
        memset(chainHead , -1, sizeof(chainHead));
        for(int i = 0; i < MXN ; i++)
            adj[i].clear();
        baseCount = -1;
        cs++;
        scanf("%d",&N);
        for(int i = 0; i < N; i++)
            scanf("%d",&ar[i]);
        int u,v;
        for(int i = 1; i < N; i++)
        {
            scanf("%d %d",&u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0 , -1 , 0);
        hld(0 , -1);
        lca_init();
        make_tree(1 , 0 , baseCount);
        int q, cmd , a , b;
        scanf("%d",&q);
        printf("Case %d:\n", cs);
        for(int i = 0; i < q; i++)
        {
            scanf("%d %d %d",&cmd , &a, &b);
            if(cmd)
            {
                change(a , b);
            }
            else
            {
                int res = query(a , b);
                printf("%d\n", res);
            }
        }
    }
    return 0;
}
