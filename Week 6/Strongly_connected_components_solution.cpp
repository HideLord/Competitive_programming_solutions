#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)((x).size())
#define mp make_pair

using namespace std;

typedef unsigned long long ull;
typedef pair<int,int> ii;

template<class U,class T>ostream& operator<<(ostream& out, pair<U,T> & P){
    return out << "[" << P.first << ", " << P.second << "]";
}
template<class T>ostream& operator<<(ostream& out, vector<T> & V){
    if(!V.empty())out << "[";
    for(int i = 0; i < sz(V); i++)out << V[i] << (i+1==sz(V)?"]":", ");
    return out;
}

vector<vector<int>> V, reversedV, segments;
int N, M;

void getTopological(int v, vector<int>& topological, bool* used){
    if(used[v])return;
    used[v] = true;
    for(auto u:V[v])getTopological(u, topological, used);
    topological.push_back(v);
}

void getSegment(int v, vector<int> &segment, bool* used){
    if(used[v])return;
    used[v] = true;
    segment.push_back(v);
    for(auto u:reversedV[v])getSegment(u,segment,used);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> N >> M;
    bool *used = new bool[N+10]{};
    V.resize(N+10);
    reversedV.resize(N+10);
    for(int i = 0; i < M; i++){
        int u,v;
        cin >> u >> v;
        V[u].push_back(v);
        reversedV[v].push_back(u);
    }
    vector<int> topological;
    getTopological(1,topological,used);
    cout << "topological: " << topological << endl;
    memset(used,0,N+1);
    for(auto it = topological.rbegin(); it!= topological.rend(); it++){
        if(used[*it])continue;
        segments.push_back(vector<int>());
        getSegment(*it,segments.back(),used);
    }

    for(auto seg:segments){
        cout << seg << endl;
    }
    delete[] used;
}
/*
9 11
1 2
2 3
1 3
3 7
7 1
7 8
8 4
4 5
5 6
6 4
5 9
*/