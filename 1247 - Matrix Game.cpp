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
        cin>>r>>c;
        int ar[r+1][c+1];
        for(int i = 0; i < r ; i++)
        {
            for(int j = 0; j < c ; j++)
            {
                cin>>ar[i][j];
            }
        }
        int row[r+1];
        for(int i = 0; i < r ; i++)
        {
            row[i] = 0;
            for(int j = 0; j < c ; j++)
            {
                row[i] +=ar[i][j];
            }
        }
        int res = 0;
        for(int i = 0; i < r ; i++)
        res = res ^ row[i];
        if(res)
        cout<<"Case "<<cs<<": Alice"<<endl;
        else
        cout<<"Case "<<cs<<": Bob"<<endl;

    }
    return 0;
}

