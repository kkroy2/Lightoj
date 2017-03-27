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
        int r , c;
        cin>>r;
        c = r;
        int black[r+1];
        int white[c+1];
        for(int i = 0; i < r ; i++)
        {
            cin>>white[i];

        }
        for(int i = 0; i < r ; i++)
        {
            cin>>black[i];

        }
        int res = 0;
        for(int i = 0; i < r ; i++)
        res = res ^ (black[i] - white[i] - 1);
        if(res)
        cout<<"Case "<<cs<<": white wins"<<endl;
        else
        cout<<"Case "<<cs<<": black wins"<<endl;

    }
    return 0;
}
