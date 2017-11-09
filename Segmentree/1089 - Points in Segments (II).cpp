#include<bits/stdc++.h>
using namespace std;

int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    vector< int > St , En;
    while(tc--)
    {
        cs++;
        int n , q;
        cin>>n>>q;
        for(int i = 0 ; i < n ; i++)
        {
            int p,q;
            scanf("%d %d",&p , &q);
            St.push_back(p);
            En.push_back(q);
        }
        sort(St.begin(), St.end());
        sort(En.begin() ,En.end());
        printf("Case %d:\n",cs);
        for(int i = 0 ; i < q ; i++)
        {
            int x;
            scanf("%d",&x);
            int s = upper_bound(St.begin(), St.end() , x) - St.begin();
            int e = lower_bound(En.begin() , En.end() , x)  - En.begin();
            printf("%d\n", s - e);
        }
        St.clear();
        En.clear();
    }
    return 0;
}
