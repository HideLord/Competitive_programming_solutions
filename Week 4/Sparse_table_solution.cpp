#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) int((x).size())
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

template<class T, class U>
ostream& operator<<(ostream& out, pair<T,U> &P){
    out << "[" << P.first << ", " << P.second << "]";
    return out;
}

template<class T>
ostream& operator<<(ostream& out, vector<T> &V){
    cout << '[';
    for(int i(0); i < sz(V); i++)out << V[i] << (i+1==sz(V)?"]":", ");
    return out;
}

const int MAX_N = 1e5;
struct sparseTable{
    vector<int> B[MAX_N+1];
    vector<ii> base2;
    #define op(a,b) min((a),(b))
    sparseTable(vector<int> &V){
        for(int i = 0, j = 1, k = 0; i <= sz(V); i++){
            if(j<<1 < i)j<<=1, k++;
            base2.push_back({j,k});
        }
        for(int i = 0; 1<<i < sz(V); i++)
            for(int j = 0; j < sz(V); j++)
                if(i==0)B[j].push_back(V[j]);
                else if(j+(1<<i-1)>=sz(V))B[j].push_back(B[j][i-1]);
                else B[j].push_back(op(B[j][i-1],B[j+(1<<i-1)][i-1]));
    }
    int query(int l, int r){ // [l,r)
        auto [range,ind] = base2[r-l];
        return op(B[l][ind],B[r-range][ind]);
    }
    #undef op
};

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    vector<int> V(10);
    iota(all(V),1);
    sparseTable ST(V);
    for(int i = 0; i < sz(V); i++)cout << ST.query(i,sz(V)) << endl;
}   