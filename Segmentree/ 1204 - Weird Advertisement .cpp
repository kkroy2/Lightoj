#include<bits/stdc++.h>
using namespace std;
const int mxn = 7*1e4 + 10;
struct input
{
	long long x1 , y1 , y2;
	int open;
	input(long long _x1 , long long _y1 , long long _y2 ,int _open)
	{
		x1 = _x1;
		y1 = _y1;
		y2 = _y2;
		open = _open;
	}
	bool operator<(const input &in) const{
	
		return x1 < in.x1;
	}
};
vector< input > ar;
long long actual[mxn+10];
set<  long long > s;
vector< long long > idx;
int n , k;
map< long long , int > mp;
struct data
{
	int cp;
	long long sum;
	long long rangeSum;
}tree[4*mxn];
void build(int node , int beg , int endd)
{
	if(beg==endd)
	{
		tree[node].rangeSum = actual[beg];
		tree[node].cp = 0;
		tree[node].sum = 0;
		return;
	}
	int left = node << 1;
	int right = left + 1;
	int mid = (beg + endd) >> 1;
	
	build(left , beg , mid);
	build(right, mid+1 , endd);
	tree[node].rangeSum = tree[left].rangeSum + tree[right].rangeSum;
	return;
}
void update(int node , int beg , int endd, int l , int r , int val, int up)
{
	if(l > r)
	return;
	int left = node << 1;
	int right = left + 1;
	int mid = ( beg + endd) >> 1;
	if(beg==endd)
	{
		tree[node].cp += val;
		if(tree[node].cp + up >= k)
		tree[node].sum = tree[node].rangeSum;
		else
		tree[node].sum = 0;
		return;
	}
	if(beg==l && endd==r)
	{
		tree[node].cp +=val;
		if( tree[node].cp+up >= k)
		{
			tree[node].sum = tree[node].rangeSum;
		}
		else
		{
			update(left, beg , mid , l , min(r , mid) ,0 , tree[node].cp + up);
	        update(right , mid+1 , endd , max(l , mid+1) , r , 0 , tree[node].cp + up);
	        if(tree[node].cp + up >= k)
			{
				tree[node].sum = tree[node].rangeSum;
			}
			else
			{
				tree[node].sum = tree[left].sum + tree[right].sum;
			}
		}
		return;
	}
	
	update(left, beg , mid , l , min(r , mid) , val , tree[node].cp + up);
	update(right , mid+1 , endd , max(l , mid+1) , r , val ,tree[node].cp + up);
	if(tree[node].cp + up >= k)
	{
		tree[node].sum = tree[node].rangeSum;
	}
	else
	{
		tree[node].sum = tree[left].sum + tree[right].sum;
	}
	return;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin>>tc;
	int cs = 0;
	while(tc--)
	{
		cs++;
		cin>>n>>k;
		int x1 , x2 , y1 , y2;
		for(int i = 1; i <= n; i++)
		{
			cin>>x1>>y1>>x2>>y2;
			
			ar.push_back( input(x1 , y1 , y2 , 1));
			ar.push_back( input(x2 , y1 , y2 , -1 ));
			s.insert(y1);
			s.insert(y2);
		}
		set< long long > :: iterator it;
		for(it = s.begin(); it!= s.end(); it++)
		{
			idx.push_back(*it);
		}
		actual[0] = 1;
		for(int i =1 ; i < idx.size(); i++)
		{
			actual[i] = idx[i] - idx[i-1];
		}
		for(int i = 0; i < idx.size() ; i++)
		{
			mp[idx[i]] = i;
		}
		build(1, 0 , idx.size()-1 );
		sort(ar.begin(), ar.end());
		int prev = ar[0].x1 -1;
		long long ans = 0;
		for(int i = 0; i < ar.size(); i++)
		{
			if(ar[i].open == 1)
			update(1 , 0 , idx.size()-1 , mp[ar[i].y1] , mp[ar[i].y2], ar[i].open, 0);
			ans += (long long)(ar[i].x1 - prev)*(long long)tree[1].sum;
			prev = ar[i].x1;
			if(ar[i].open == -1)
			update(1 , 0 , idx.size()-1 , mp[ar[i].y1] , mp[ar[i].y2], ar[i].open , 0);

		}
		cout<<"Case "<<cs<<": "<<ans<<endl;
		ar.clear();
		idx.clear();
		s.clear();
		mp.clear();
		memset(actual, 0 , sizeof actual);
	}
	return 0;
}
