#include<bits/stdc++.h>
using namespace std;
const int mxn = 200000 + 20;
int ar[mxn] ,  lm[mxn], tp[mxn];
bool tmp[mxn];
int n;
int tree[4*mxn + 20];
typedef long long ll;
void make(int node , int beg , int endd)
{
	if(beg==endd)
	{
		tree[node] = ar[beg];
		return;
	}
	int left = node << 1;
	int right = left+1;
	int mid = (beg + endd)>>1;
	make(left, beg, mid);
	make(right , mid+1 , endd);
	tree[node] = max(tree[left] , tree[right]);
	return;
}
int query(int node , int beg, int endd, int i , int j)
{
	if(i > j)
	return 0;
	if(i==beg && j==endd)
	{
		return tree[node];
	}
	int left = node << 1;
	int right = left+1;
	int mid = (beg + endd)>>1;
	int l =  query(left , beg , mid , i , min(mid , j));
	int r = query(right, mid+1 , endd , max(mid+1 , i) ,j);
	return max(l, r);
}
ll dp[2*mxn+100];
ll solve(int pos)
{
	if(pos >= n)
	return 0;
	if(dp[pos]!=-1)
	{
		return dp[pos];
	}
	ll mn = 1e16;
	for(int i = pos ; i <= lm[pos] ; i++)
	{
		mn = min(mn , solve(i+1) + query(1 , 0 , n-1 , pos , i));
	}
	return dp[pos] = mn;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin>>tc;
	int cs= 0;
	while(tc--)
	{
		cs++;
		cin>>n;
		for(int i = 0; i < n; i++)
		{
			cin>>tp[i]>>ar[i];
		}
		memset(tmp , false , sizeof tmp);
		int left = 0, right = 1;
		tmp[tp[0]] = true;
		while(left < n)
		{
			while(!tmp[tp[right]] && n > right)
			{
				tmp[tp[right]] = true;
				right++;
			}
			lm[left] = right-1;
			tmp[tp[left]] = false;
			left++;
		}
		make(1 , 0 , n-1);
		memset(dp , -1 , sizeof dp);
		ll ans = solve(0);
		cout<<"Case "<<cs<<": "<<ans<<endl;
	}
	
	return 0;
}
