#include<bits/stdc++.h>
using namespace std;
#define MXN 1429431

int tree[4*MXN];

void make_tree(int node , int beg , int endd)
{
    if(beg == endd)
    {
        tree[node] = 1;
        return;
    }

    int left = node << 1;
    int mid = (beg + endd) >> 1;

    make_tree(left , beg , mid);
    make_tree(left+1 , mid+1 , endd);
    tree[node] = tree[left] + tree[left+1];
    return ;
}

int query(int node , int beg , int endd , int val)
{
    if(beg==endd)
    {
        return beg;
    }

    int mid = (beg + endd) >> 1;
    int left = node << 1;
    if(tree[left] < val)
    {
        return query(left + 1 , mid+1 , endd , val - tree[left]);
    }
    else
        return query(left , beg , mid , val);

}

void update(int node , int beg , int endd , int val)
{
    if(beg==endd)
    {
        tree[node] = 0;
        return;
    }

    int left = node << 1;
    int mid = (beg + endd) >> 1;
    if(tree[left] < val)
    update(left + 1 , mid+1 , endd , val - tree[left]);
    else
    {
        update(left , beg, mid , val);
    }
    tree[node] = tree[left] + tree[left+1];
    return;
}

int main()
{
    make_tree(1 , 1 , MXN);
    int pos = 2 , tmp, cnt;
    bool flag = false;
    while(tree[1] > 100000)
    {
         tmp = query(1 , 1 ,MXN , pos);
         cnt = tmp;
        while(tree[1] >= tmp)
        {
            update(1 , 1 , MXN , tmp);
            tmp += cnt -1;
        }
        if(flag)
        pos ++;
        flag = true;
    }
    int tc;
    scanf("%d",&tc);
    int cs = 0, n;
    while(tc--)
    {
        cs++;
        scanf("%d",&n);
        printf("Case %d: %d\n" ,cs, query(1 , 1 , MXN , n));
    }
    return 0;
}
