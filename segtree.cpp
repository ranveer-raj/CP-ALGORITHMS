#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
// value at ith index can be found by --> *st.find_by_order(i)
// index of number (num) can be found by --> st.order_of_key(num)
// if number (num) is not in the set then it will show the last index number i.e. st.end()
#endif

#define int long long
#define double long double
#define space " "
#define endl "\n"
#define intmin LLONG_MIN
#define intmax LLONG_MAX
#define infinity ULLONG_MAX
#define bitcount(x) __builtin_popcountll(x)
#define setbit(x, i) (x | (1LL << i))
#define unsetbit(x, i) (x & (~(1LL << i)))
#define flipbit(x, i) (x ^ (1LL << i))
#define checkbit(x, i) ((x >> i) & 1LL)
#define msb(x) (63 - (__builtin_clzll(x)))
#define lsb(x) ((__builtin_ctzll(x)))
#define itob(x) bitset<64>(x).to_string()

#ifndef ONLINE_JUDGE
#define debarr(a,n)cerr<<#a<<":";for(int i=0;i<n;i++)cerr<<a[i]<<" ";cerr<<endl;
#define debmat(mat,row,col)cerr<<#mat<<":\n";for(int i=0;i<row;i++){for(int j=0;j<col;j++)cerr<<mat[i][j]<<" ";cerr<<endl;}
#define pr(...)dbs(#__VA_ARGS__,__VA_ARGS__)
template<class S,class T>ostream &operator<<(ostream &os,const pair<S,T> &p){return os<<"("<<p.first<<","<<p.second<<")";}
template<class T>ostream &operator<<(ostream &os,const vector<T> &p){os<<"[";for(auto&it:p)os<<it<<" ";return os<<"]";}
template<class T>ostream &operator<<(ostream &os,const set<T>&p){os<<"[";for(auto&it:p)os<<it<<" ";return os<<"]";}
template<class T>ostream &operator<<(ostream &os,const multiset<T>&p){os<<"[";for(auto&it:p)os<<it<<" ";return os<<"]";}
template<class S,class T>ostream &operator<<(ostream &os,const map<S,T>&p){os<<"[";for(auto&it:p)os<<it<<" ";return os<<"]";}
template<class T>void dbs(string str,T t){cerr<<str<<":"<<t<<"\n";}
template<class T,class...S>void dbs(string str,T t,S... s){int idx=str.find(',');cerr<<str.substr(0,idx)<<":"<<t<<",";dbs(str.substr(idx+1),s...);}
#else
#define pr(...){}
#define debarr(a,n){}
#define debmat(mat,row,col){}
#endif

const int mod = 1000000007;
const int inf = 1e18;
const double pi = acos(-1.0);
const int nax1 = 100001;
const int nax2 = 1000001;
const int nax3 = 10000001;


/******************* Segment Tree Start Here ************************/
// This code is written for Range Minimum Query
// define node according to question
// change merge function according to question

struct node
{
    int num;
    node(int x=inf)
    {
        num = x;
    }
};

node merge(node a, node b)
{
    if (a.num < b.num)
    {
        return a;
    }
    else
    {
        return b;
    }
}

vector<int> arr;
vector<node> segt;

void build(int index, int l, int r)
{
    if (l == r)
    {
        segt[index] = node(arr[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(index * 2, l, mid);
    build(index * 2 + 1, mid + 1, r);
    segt[index] = merge(segt[index * 2], segt[index * 2 + 1]);
}

void update(int index, int l, int r, int pos, int val)
{
    if (pos < l || pos > r)
    {
        return;
    }
    if (l == r)
    {
        segt[index] = node(val);
        arr[pos] = val;
        return;
    }
    int mid = (l + r) / 2;
    update(index * 2, l, mid, pos, val);
    update(index * 2 + 1, mid + 1, r, pos, val);
    segt[index] = merge(segt[index * 2], segt[index * 2 + 1]);
}

node query(int index, int l, int r, int lq, int rq)
{
    if (l > rq || r < lq)
    {
        return node(inf);
    }
    if (l >= lq && r <= rq)
    {
        return segt[index];
    }
    int mid = (l + r) / 2;
    return merge(query(index * 2, l, mid, lq, rq), query(index * 2 + 1, mid + 1, r, lq, rq));
}

/******************* Segment Tree End Here ************************/

void solve()
{
    int n, m;
    cin >> n >> m;
    segt.resize(4 * n);
    arr.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    build(1, 0, n - 1);
    for (int i = 0; i < m; i++)
    {
        int ch, y, z;
        cin >> ch >> y >> z;
        if (ch == 1)
        {
            update(1, 0, n - 1, y, z);
        }
        else if (ch == 2)
        {
            cout << query(1, 0, n - 1, y, z).num << endl;
        }
    }
}

signed main()
{
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // freopen("error.txt", "w", stderr);
    // #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // int _t=1;cin>>_t;while(_t--)
    solve();
    return 0;
}