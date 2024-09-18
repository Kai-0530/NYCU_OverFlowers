// O(sqrt(V)E)
struct Graph{
    static const int MAXN = 4005;
    vector<int> G[MAXN];
    int N1, N2, match[MAXN], dist[MAXN];
 
    void init(int _n1, int _n2){
        N1 = _n1; 
        N2 = _n2; 
        for (int i = 0; i < N1 + N2; i++) G[i].clear();
    }
 
    void addEdge(int u, int v){
        G[u].pb(v + N2); 
    }
 
    bool bfs(){
        queue<int> Q;
        for (int u = 0; u < N1; u++){
            if (match[u] == -1){
                dist[u] = 0;
                Q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!Q.empty()){
            int u = Q.front(); Q.pop();
            for (int v : G[u]){
                int m = match[v];
                if (m != -1 && dist[m] != -1) continue;
                if (m != -1){
                    dist[m] = dist[u] + 1;
                    Q.push(m);
                } else {
                    found = true;
                }
            }
        }
        return found;
    }
 
    bool dfs(int u){
        for (int v : G[u]){
            int m = match[v];
            if (m == -1 || (dist[m] == dist[u] + 1 && dfs(m))){
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
 
    int solve(){
        int res = 0;
        memset(match, -1, sizeof(match));
        while (bfs()){
            for (int u = 0; u < N1; u++){
                if (match[u] == -1){
                    if (dfs(u)) res++;
                }
            }
        }
        return res;
    }
} graph;

/*
graph.init(n1, n2) : 2 parts' node numbers
graph.addEdge(i, j) : edge i->j
graph.solve(): match numbers
*/