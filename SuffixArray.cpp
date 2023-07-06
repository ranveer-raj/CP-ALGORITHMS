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

class SuffixArray
{
    private:
        vector<int> RA;
        void countingSort(int k)
        {
            int maxi = max(300LL, n);
            vector<int> c(maxi, 0);
            for (int i = 0; i < n; ++i) ++c[i + k < n ? RA[i + k] : 0];
            for (int i = 0, sum = 0; i < maxi; ++i)
            {
                int t = c[i];
                c[i] = sum;
                sum += t;
            }
            vector<int> tempSA(n);
            for (int i = 0; i < n; ++i) tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
            swap(SA, tempSA);
        }
        void constructSA()
        {
            SA.resize(n);
            iota(SA.begin(), SA.end(), 0);
            RA.resize(n);
            for (int i = 0; i < n; ++i)
            RA[i] = T[i];
            for (int k = 1; k < n; k <<= 1)
            {
                countingSort(k);
                countingSort(0);
                vector<int> tempRA(n);
                int r = 0;
                tempRA[SA[0]] = r;
                for (int i = 1; i < n; ++i) tempRA[SA[i]] = ((RA[SA[i]] == RA[SA[i - 1]]) && (RA[SA[i] + k] == RA[SA[i - 1] + k])) ? r : ++r;
                swap(RA, tempRA);
                if (RA[SA[n - 1]] == n - 1) break;
            }
        }
        void computeLCP()
        {
            vector<int> Phi(n);
            vector<int> PLCP(n);
            PLCP.resize(n);
            Phi[SA[0]] = -1;
            for (int i = 1; i < n; ++i) Phi[SA[i]] = SA[i - 1];
            for (int i = 0, L = 0; i < n; ++i)
            {
                if (Phi[i] == -1)
                {
                    PLCP[i] = 0;
                    continue;
                }
                while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L])) ++L;
                PLCP[i] = L;
                L = max(L - 1, 0LL);
            }
            LCP.resize(n);
            for (int i = 0; i < n; ++i) LCP[i] = PLCP[SA[i]];
        }
    public:
        const string T;
        const int n;
        vector<int> SA;
        vector<int> LCP;
        SuffixArray(const string &initialT) : T(initialT+"$"), n((int)initialT.size()+1LL)
        {
            constructSA();
            computeLCP();
            SA.erase(SA.begin());
            LCP.erase(LCP.begin());
        }
};

void solve()
{
    string str;
    cin>>str;
    int n = str.size();
    SuffixArray S(str);
    cout<<"i SA[i] LCP[i]\n";
    for (int i = 0; i < n; ++i)
    {
        cout<<i<<"    "<<S.SA[i]<<"    "<<S.LCP[i]<<endl;
    }
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
