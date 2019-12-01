#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) int((x).size())
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

template<class U,class T>ostream& operator<<(ostream& out, pair<U,T> & P){
    return out << "[" << P.first << ", " << P.second << "]";
}
template<class T>ostream& operator<<(ostream& out, vector<T> & V){
    if(!V.empty())out << "[";
    for(int i = 0; i < sz(V); i++)out << V[i] << (i+1==sz(V)?"]":", ");
    return out;
}
struct SegmentTree{
    vector<int> seg;
    int N;
    const int defaultVal = 0;
    #define op(a,b) ((a)+(b))
    SegmentTree(vector<int> &V){
        seg.assign(2<<(int)ceil(log2(sz(V))), defaultVal); // The closest power of two(bigger than sz(V)) times 2
        N = sz(seg)>>1; // the starting point for the non aggregated values
        copy(V.begin(),V.end(),seg.begin()+N); // Copy the vector V to the appropriate place in seg
        for(int i=N-1; i; i--)seg[i]=op(seg[i<<1],seg[i<<1|1]); // Left and right branch (i<<1 is always even, so i<<1|1 is always odd. This means that they are always left/right)
    }
    void modify(int k, int val){// if k is even then k^1 is the odd and otherwise if k is odd then k^1 is even, so in both cases left and right children
        for(seg[k+=N]=val; k; k>>=1)seg[k>>1]=op(seg[k],seg[k^1]); 
    }
    int query(int l,int r){ // [l,r)
        int res = defaultVal;
        for(l+=N,r+=N; l<r; l>>=1,r>>=1){
            if(l&1) res=op(res,seg[l++]); // if it's right child, then add it and go to right branch since no more values are needed from current branch.
            if(r&1) res=op(res,seg[--r]); // if it's right child (since it's noninclusive range right is not added), then add left child and continue up.
        }
        return res;
    }
    #undef op
};
int main(){
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    vector<int> V={1,2,3,4,5,6,7,8,9,10};
    SegmentTree st(V);
    st.modify(9,0);
    for(int i = 0; i < sz(V); i++)cout << st.query(i,sz(V)) << endl;
}