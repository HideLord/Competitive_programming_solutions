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
// A struct for the edge
struct Edge{
    int to; 
    Edge* opposite;
    int flow;
    int cap;
    // returns the remaining capacity
    int rc(){ return cap - flow; }
};
vector<vector<Edge*>> edges;

// Sorts the vertice by level and checks if there is still a path between start and end
bool bfs(int start, int end, vector<int>& level){
    fill(level.begin(),level.end(),-1);
    queue<int> Q;
    Q.push(start);
    level[start] = 0;
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        cout << v << " " << edges[v].size() << endl;
        for(auto u:edges[v]){
            if(level[u->to]==-1 && u->rc()>0){
                Q.push(u->to);
                level[u->to] = level[v]+1;
            }
        }
    }
    return level[end]!=-1;
}

// Calculates the flow of the shortest path from start to end
int dfs(int u, int f, int end, vector<int>& level, vector<int>& start){
    if (u == end) return f; 
    for (;start[u] < edges[u].size(); start[u]++) { 
        Edge *e = edges[u][start[u]];
        if (level[e->to] == level[u]+1 && e->rc() > 0){ 
            int res = dfs(e->to, min(f, e->rc()), end, level, start);
            if (res) { 
                e->flow += res; 
                e->opposite->flow -= res; 
                return res; 
            } 
        } 
    }
    return 0;
}

int maxFlow(int s, int e){
    vector<int> level(edges.size());
    vector<int> start(edges.size());
    int cumulative = 0, flow;
    while(bfs(s,e,level)){
        cout << "Nice a bfs was found" << endl;
        fill(start.begin(),start.end(),0);
        while(flow = dfs(s,1e9,e,level,start))
            cumulative += flow;
    }
    return cumulative;
}

void addEdge(int from, int to, int cap){
    Edge* straight = new Edge();
    Edge* gay = new Edge();
    straight->to = to;
    straight->opposite = gay;
    straight->flow = 0;
    straight->cap = cap;
    gay->to = from;
    gay->opposite = straight;
    gay->flow = -cap;
    gay->cap = 0;
    edges[from].push_back(straight);
    edges[to].push_back(gay);
}

void free(){
    for(int i = 0; i < edges.size(); i++)
        for(int j = 0; j < edges[i].size(); j++)
            delete edges[i][j];
}

int main(){
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    edges.resize(N);
    for(int i = 0; i < M; i++){
        int from, to, flow;
        cin >> from >> to >> flow;
        addEdge(from,to,flow);
    }
    cout << maxFlow(0, N-1) << endl;
    free();
    return 0;
}