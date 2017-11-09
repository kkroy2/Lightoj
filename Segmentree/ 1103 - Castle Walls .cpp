#include<bits/stdc++.h>
using namespace std;
const int mxn = 2*1e5 + 10;
struct input
{
	int st , en;
	input(int _st , int _en)
	{
		st = _st;
		en = _en;
	}
	bool operator <(const input &i) const
	{
		return st < i.st;
	} 
};
vector<input > in;
int tree[4*mxn];
void update(int node , int beg , int endd, int pos)
{
	if(pos==beg  && pos==endd)
	{
		tree[node] +=1;
		return;
	}
	int left = node << 1;
	int right = left + 1;
	int mid = (beg + endd) >> 1;
	if(pos <= mid)
	{
		update(left, beg , mid , pos);
	}
	else
	{
		update(right , mid+1 , endd, pos);
	}
	tree[node] = tree[left] + tree[right];
	return;
}
int query(int node , int beg, int endd , int l , int r)
{
	if(l > r)
	return 0;
	if(l==beg && endd==r)
	{
		return tree[node];
	}
	int left = node << 1;
	int right = left + 1;
	int mid = (beg + endd ) >> 1;
	int lr = query(left , beg , mid , l , min(mid, r));
	int rr = query(right, mid+1 , endd , max(mid+1 , l) , r);
	return lr + rr;
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
		memset(tree, 0 , sizeof tree);
		cs++;
		int n, m;
		int x1, y1;
		cin>>n>>m;
		for(int i = 0; i < n+m; i++)
		{
			cin>>x1>>y1;
			in.push_back(input(x1 , y1));
		}
		sort(in.begin(), in.end());
		long long ans = 0;
		for(int i = 0; i < in.size(); i++)
		{
			ans += query(1 ,1 , n+m, in[i].en , n+m);
			update(1 ,1  , n+m , in[i].en);
		}
		cout<<"Case "<<cs<<": "<<ans<<endl;
		in.clear();
	}
	return 0;
}
