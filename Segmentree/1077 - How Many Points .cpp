#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a , long long b)
{
    if(b==0)
        return a;
    return gcd(b , a%b);
}

int main()
{
    int tc;
    cin>>tc;
    int cs = 0;
    while(tc--)
    {
        cs++;
        long long int x1 , y1 , x2 , y2;
        cin>>x1>>y1>>x2>>y2;
        long long  res =gcd(llabs(x1 - x2) , llabs(y1 - y2));
        cout<<"Case "<<cs<<": "<<res+1<<endl;
    }
    return 0;
}
