#include<bits/stdc++.h>
using namespace std;

struct Edge
{
    int w , v, u;
} e;

vector< Edge > E;

bool operator< ( Edge a , Edge b)
{
    return a.w < b.w;
}
int n , parent[55] , sum;

int find_parent(int x)
{
    if(parent[x]==x)
        return parent[x];
    return parent[x] = find_parent(parent[x]);
}

void krs()
{
    sort(E.begin() , E.end());
    for(int i = 1; i <= n ; i++)
        parent[i] = i;
    int sz = E.size();
    sum = 0;
    int ans = 0;
    for(int i = 0; i < sz ; i++)
    {
        sum+=E[i].w;
        if(find_parent(E[i].u)!=find_parent(E[i].v) && E[i].w!=0)
        {
            parent[parent[E[i].u]] = parent[E[i].v];
            ans+=E[i].w;
        }
    }
    sum -=ans;
}
int main()
{
    int tc ;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        //cin>>n;
        scanf(" %d",&n);
        int x;
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
               // cin>>x;
               scanf(" %d",&x);
                if(x)
                {
                    e.u = i;
                    e.v = j;
                    e.w = x;
                    E.push_back(e);
                }
            }
        }
        krs();
        bool flag = false;
        for(int i = 1 ; i < n ; i++)
        {
            if(find_parent(i)!=find_parent(i+1))
            {
                flag = true;
                break;
            }
        }
        if(flag )
        {
            //cout<<"Case "<<cs<<": -1"<<endl;
            printf("Case %d: -1\n",cs);
        }
        else
            //cout<<"Case "<<cs<<": "<<sum<<endl;
            printf("Case %d: %d\n",cs,sum);
        sum = 0;
        E.clear();

    }
    return 0;
}
