#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) int((x).size())

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

template<class T, class U>
ostream& operator<<(ostream& out, pair<T,U> &P){
    return out << "[" << P.first << ", " << P.second << "]";
}

template<class T>
ostream& operator<<(ostream& out, vector<T> &V){
    cout << '[';
    for(int i(0); i < sz(V); i++)out << V[i] << (i+1==sz(V)?"]":", ");
    return out;
}

template<class T> struct Node{
    vector<T> vals;
    #define def 0
    T res = def;
    #define op(a,b) ((a)+(b)) // The operation must be commutative
    Node(const int SZ){
        vals.assign(SZ,def);
    }
    constexpr int size() const {return sz(vals);}
    void reeval(){
        res = def;
        for(auto &i:vals) res = op(res,i);
    }
    void modify(int ind, T val){
        vals[ind] = val;
        reeval();
    }
    Node split(int l){ // [0,l),[l,SIZE)
        Node<T> next(sz(vals)-l);
        for(int i = 0;l<sz(vals); l++)next.vals[i++] = vals[l];
        next.reeval();
        vals.resize(l);
        reeval();
        return next;
    }
    T query(int l, int r){// [l,r)
        T res = def;
        while(l<r)res = op(res,vals[l++]);
        return res;
    }
    T query(){ return res; }
};
template<class T> struct sqrtD{
    list<Node<T>> nodes;
    sqrtD(vector<int> &V){
        int nodeSize = ceil(sqrt(sz(V)));
        Node<T> n(nodeSize);
        for(int i = 0, curr = 0; i < sz(V); i++,curr++){
            if(curr==nodeSize){
                curr = 0;
                n.reeval();
                nodes.push_back(n);
                n.vals.assign(nodeSize,def);
            }
            n.vals[curr]=V[i];
        }
        n.reeval();
        nodes.push_back(n);
    }
    void split(typename list<Node<T>>::iterator it, int l){ // Splits in [0,l), [l,sqrtSize)
        Node<T> next = it->split(l);
        nodes.insert(it,next);
    }
    void merge(typename list<Node<T>>::iterator it){ // merges it and it->next
        auto next = std::next(it);
        it->vals.insert(it->vals.end(),all(next->vals));
        nodes.erase(next);
        it->reeval();
    }
    void modify(int ind, T val){
        int curr = 0;
        for(auto &n: nodes){
            if(curr<=ind && curr+sz(n)>ind){
                n.modify(ind-curr, val);
                break;
            }
            curr+=sz(n);
        }
    }
    T query(int l, int r){// [l,r)
        int curr = 0;
        T res = def;
        for(auto &n: nodes){
            if(curr<=l && curr+sz(n)>l){
                if(curr<=r && curr+sz(n)>=r)
                    return n.query(l-curr,r-curr);
                res = op(n.query(l-curr,sz(n)),res);
            }else if(curr>l && curr+sz(n)<=r){
                res = op(n.query(),res);
            }else if(curr<r && curr+sz(n)>=r){
                res = op(n.query(0,r-curr),res);
                return res;
            }
            curr+=sz(n);
        }
        return res;
    }
};

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    vector<int> V(100);
    iota(all(V),1);
    sqrtD<int> sd(V);
    int real_res = 0, l=2,r=23;
    sd.modify(13,0);
    sd.merge(sd.nodes.begin());
    V[13] = 0;
    for(int i = l; i < r; i++)real_res=op(V[i],real_res);
    cout << "wanted: " << real_res << endl;
    cout << sd.query(l,r) << endl;
}