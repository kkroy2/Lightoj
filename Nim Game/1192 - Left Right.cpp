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
        int n;
        cin>>n;
        int ar[2*n + 1];
        for(int i = 0 ; i < 2*n ; i++)
        cin>>ar[i];
        int res = 0;
        for(int i = 0 ; i < 2*n ; i+=2)
        {
            res = res ^( ar[i+1] - ar[i] - 1);
        }
        if(res)
        cout<<"Case "<<cs<<": Alice"<<endl;
        else
        cout<<"Case "<<cs<<": Bob"<<endl;
    }

    return 0;
}
