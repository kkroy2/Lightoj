#include<bits/stdc++.h>
using namespace std;

int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        int r ;
        cin>>r;
        int ar[r+1];
        int mx = 0;
        for(int i = 0; i < r ; i++)
        {
                cin>>ar[i];
                mx = max(mx , ar[i]);
        }
        if(mx == 1)
        {
            if(r&1)
            {
                cout<<"Case "<<cs<<": Bob"<<endl;
            }
            else
            cout<<"Case "<<cs<<": Alice"<<endl;
        }
        else{
        int res = 0;
        for(int i = 0; i < r ; i++)
        res = res ^ ar[i];
        if(res)
        cout<<"Case "<<cs<<": Alice"<<endl;
        else
        cout<<"Case "<<cs<<": Bob"<<endl;
    }
    }
    return 0;
}

