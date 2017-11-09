#include<bits/stdc++.h>
using namespace std;
const int mxn = 2*1e5 + 10;
struct Type
{
	long long typ , ht;
} ar[mxn];
int n;
int lw[mxn]  , cnt[mxn];
typedef long long ll;
struct Data
{
	ll pre_cost;
	ll lazy_value;
	bool lazy_flag;
}tree[mxn*4];
struct Range
{
	ll ht;
	int l , r;
};
void prop(int node , int left , int right)
{
	tree[left].pre_cost = tree[left].pre_cost + tree[node].lazy_value;
	tree[right].pre_cost = tree[right].pre_cost + tree[node].lazy_value;
	tree[left].lazy_flag = true;
	tree[right].lazy_flag = true;
	tree[left].lazy_value = tree[node].lazy_value;
	tree[right].lazy_value = tree[node].lazy_value;
	tree[node].lazy_flag = false;
	return;
}

void update(int node , int beg, int endd , int l , int r , ll val)
{
	if( l > r)
	return;
	if(beg == l && endd == r)
	{
		tree[node].lazy_value = val;
		tree[node].pre_cost = tree[node].pre_cost + val;
		tree[node].lazy_flag = true;
		return;
	}
	
	int left = node << 1;
	int right = left + 1;
	int mid = (beg + endd) >> 1;
	if(tree[node].lazy_flag)
	{
		prop(node , left , right);
	}
	update(left , beg, mid , l , min(r , mid) , val);
	update(right , mid+1, endd , max(l , mid+1) , r , val);
	tree[node].pre_cost = min(tree[left].pre_cost , tree[right].pre_cost);
	return ;
}
void point_update(int node , int  beg ,int endd , int p , int prc)
{
	if(beg==p && endd ==p)
	{
		tree[node].pre_cost = prc;
		tree[node].lazy_flag = false;
		tree[node].lazy_value = 0;
		return;
	}
	int left = node << 1;
	int right = left + 1;
	int mid = (beg + endd) >> 1;
	
	if(mid >= p)
	{
		point_update(left , beg , mid , p , prc);
	}
	else
	{
		point_update(right , mid+1, endd , p ,  prc);
	}
	tree[node].pre_cost = min(tree[left].pre_cost , tree[right].pre_cost);
	return;
}

ll query(int node, int beg , int endd , int l , int r)
{
	if( l > r)
	{
		return (long long) 1e15;
	}
	if(beg == l && endd == r)
	{
		return tree[node].pre_cost;
	}
	int left = node << 1;
	int right = left + 1;
	int mid = (beg + endd) >> 1;
	
	if(tree[node].lazy_flag)
	{
		prop(node , left , right);
	}
	ll lr = query(left , beg , mid , l , min(r , mid));
	ll rr = query(right , mid+1 , endd, max(l , mid+1) , r);
	return min( lr , rr);
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
		cin>>n;
		for(int i = 1; i <= n; i++)
		{
			cin>>ar[i].typ>>ar[i].ht;
		}
		int j = n;
		memset(cnt , 0 , sizeof cnt);
		memset(lw , 0 , sizeof lw);
		cnt[0]=1;
		for(int i = n; i > 0; i--)
		{
			while(!cnt[ar[j].typ] && j > 0)
			{
				cnt[ar[j].typ]++;
				j--;
			}
			lw[i] = j+1;
			cnt[ar[i].typ]--;
		}
		stack<Range> st;
		Range q;
		q.ht = 1e15;
		q.l = 0;
		q.r = 0;
		st.push(q);
		ll pre = 0;
		for(int i = 1; i <= n; i++)
		{
			while( st.size() > 1 && st.top().ht < ar[i].ht )
			{
				q = st.top();
				st.pop();
				cout<<q.l<<" "<<q.r<<" "<<q.ht<<" "<<ar[i].ht<<endl;
				update(1 , 0 , n , q.l , q.r , (-1)*(q.ht));
			}
			cout<<st.top().r+1<<" "<<i<<" "<<ar[i].ht<<endl;
			update(1 , 0 , n ,st.top().r+1 , i , ar[i].ht);
			q.l = st.top().r+1;
			q.r = i;
			q.ht = ar[i].ht;
			st.push(q);
			ll ret = query(1 , 0 , n , lw[i] , i);
			point_update(1 , 0 , n ,i+1, ret);
			pre = ret;
			cout<<ret<<" ret "<<ar[i].ht<<endl;
		}
		cout<<"Case "<<cs<<": "<<pre<<endl;
		while(!st.empty())
		st.pop();
		memset(tree , 0 , sizeof(tree));
	}
	return 0;
}
