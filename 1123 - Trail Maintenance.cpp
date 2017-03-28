#include<bits/stdc++.h>
using namespace std;

struct Edge
{
    int u , v, w;
} e;
vector< Edge > E , tmp;
typedef pair< int , int > PII;
int N , W , cost = 0;
int parent[202];
int find_parent( int x)
{
    if(parent[x]==x)
        return parent[x];
    return parent[x] = find_parent(parent[x]);
}
bool operator < ( Edge a , Edge b)
{
    return a.w < b.w;
}
bool krs()
{
    for(int i  = 0 ; i <= N ; i++)
        parent[i] = i;
    int sz = E.size();
    sort(E.begin(), E.end());
    for(int i = 0; i < sz ; i++)
    {
        if(find_parent(E[i].u)!= find_parent(E[i].v))
        {
            tmp.push_back(E[i]);
            cost +=E[i].w;
            parent[parent[E[i].u]] = parent[E[i].v];
        }
    }
    E.clear();
    sz = tmp.size();
    for(int i = 0; i < sz ; i++)
    {
        E.push_back(tmp[i]);
    }
    tmp.clear();
    for(int i = 1; i < N ; i++)
    {
        if(find_parent(i)!= find_parent(i+1))
            return false;
    }
    return true;

}
int main()
{
    int tc;
    cin>>tc;
    int x , y,c,cs = 0;
    while(tc--)
    {
        cs++;
        //cin>>N>>W;
        printf("Case %d:\n",cs);
        scanf("%d%d",&N , &W);
        map < PII , int > mp;
        int cnt = 0;
        for(int i = 0 ;  i < W; i++)
        {
            //cin>>x>>y>>c;
            scanf("%d %d %d", &x , &y , &c);
            e.u = x;
            e.v = y;
            e.w = c;
            cnt++;
            E.push_back(e);
            if(cnt >= N-1)
            {
                bool flag = krs();

               // cout<<parent[4]<<" "<<parent[3]<<endl;
                if(flag)
                {
                    printf("%d\n",cost);
                }
                else
                    printf("-1\n");
                cost = 0;
            }
            else
            {
                printf("-1\n");
            }

        }
        mp.clear();
        E.clear();

    }
    return 0;
}
