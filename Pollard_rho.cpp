#include<bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int , null_type, less<int> , rb_tree_tag , tree_order_statistics_node_update> ordered_set;
typedef tree<int , null_type ,  less_equal<int> , rb_tree_tag , tree_order_statistics_node_update> ordered_multiset;
// value at ith index can be found by --> *st.find_by_order(i)
// index of number (num) can be found by --> st.order_of_key(num)
// if the number (num) is not in the set then it will show the last index number i.e. st.end()
#endif

#define int long long
#define double long double
#define space " "
#define endl "\n"
#define intmin LLONG_MIN
#define intmax LLONG_MAX
#define infinity ULLONG_MAX
#define bitcount(x) __builtin_popcountll(x)
#define setbit(x,i) (x|(1LL<<i))
#define unsetbit(x,i) (x&(~(1LL<<i)))
#define flipbit(x,i) (x^(1LL<<i))
#define checkbit(x,i) ((x>>i)&1LL)
#define msb(x) (63-(__builtin_clzll(x)))
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

const int mod=1000000007;
const int inf=1e18;
const double pi=acos(-1.0);
const int nax1=100001;
const int nax2=1000001;
const int nax3=10000001;

// pollard rho algorithm (Brent version) with Miller Rabin Algorithm for primality test (Deterministic approach) to factorise a number start here
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
long long true_rand(long long n)
{
    uniform_int_distribution<long long> uid(0, n - 1);
    return uid(rng);
}
using u64 = uint64_t;
using u128 = __uint128_t;
u64 binpower(u64 base, u64 e, u64 mod) 
{
    u64 result = 1;
    base %= mod;
    while (e) 
    {
        if (e & 1) result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}
bool check_composite(u64 n, u64 a, u64 d, int s)
{
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++)
    {
        x = (u128)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}
bool MillerRabin(u64 n) // return true if prime else return false
{
    if (n < 2) return false;
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) 
    {
        d >>= 1;
        r++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) 
    {
        if (n == a) return true;
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}
long long gcd(long long a,long long b)
{
    if(a%b==0) return b;
    return gcd(b,a%b);
}
long long mult(long long a, long long b, long long mod)
{
    return (__int128)a * b % mod;
}

long long f(long long x, long long c, long long mod)
{
    return (mult(x, x, mod) + c) % mod;
}

long long brent(long long n) 
{
    if(n%2==0)  return 2;
    long long x0=(true_rand(LLONG_MAX)%(n-2))+2;
    long long c=(true_rand(LLONG_MAX)%(n-1))+1;
    long long x = x0;
    long long g = 1;
    long long q = 1;
    long long xs, y;
    int m = 128;
    int l = 1;
    while (g == 1)
    {
        y = x;
        for (int i = 1; i < l; i++)
            x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) 
        {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) 
            {
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
            g = gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) 
    {
        do 
        {
            xs = f(xs, c, n);
            g = gcd(abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}
void factor(int x,vector<int>& pf)
{
    if(x==1) return;
    if(!MillerRabin(x))
    {
        int y=brent(x);
        factor(y,pf);
        factor(x/y,pf);
    }
    else
    {
        pf.push_back(x);
        return;
    }
}
vector<int> prime_factor(int x)
{
    vector<int> pf;
    factor(x,pf);
    sort(pf.begin(),pf.end());
    return pf;
}
vector<int> all_factor(int x)
{
    vector<int> primeFactors=prime_factor(x);
    vector<int> allfactors = {1};
    for (int i = 0; i < primeFactors.size(); i++)
    {
        int currentSize = allfactors.size();
        for (int j = 0; j < currentSize; j++)
        {
            allfactors.push_back(allfactors[j] * primeFactors[i]);
        }
        set<int> st;
        for (auto v : allfactors)
        {
            st.insert(v);
        }
        allfactors.clear();
        for (auto v : st)
        {
            allfactors.push_back(v);
        }
    }
    return allfactors;
}
// pollard rho algorithm (Brent version) with Miller Rabin Algorithm for primality test (Deterministic approach) to factorise a number end here

void solve()
{
    int n;
    cin>>n;
    vector<int> primefactor=prime_factor(n);
    vector<int> allfactor=all_factor(n);
    cout<<primefactor<<endl;
    cout<<allfactor<<endl;
}

signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int _t=1;cin>>_t;while(_t--)
    solve();
    return 0;
}