// online O(nlogn + mlogn) 
const int N = 300005;
int d[N],f[N][20];// f[i][j] = i's 2^j father, d[i] = depth of i
vector<int> g[N]; // graph

void dfs(int now,int p,int dep){
    d[now] = dep+1;
    for(int nxt:g[now]){
        if(nxt==p) continue;
        f[nxt][0] = now;
        dfs(nxt,now,dep+1);
    }
    return;
}

int lca(int x, int y){
    if(d[x]<d[y]) swap(x,y);
    int k = d[x]-d[y];
    for(int i=0;i<20;i++){
        if(k&1) x = f[x][i];
        k>>=1;
    }// jump to the same depth/height
    if(x==y) return x;
    for(int i=19; i>=0;i--){
        if(f[x][i]!=f[y][i]){
            x = f[x][i];
            y = f[y][i];
        }
    }// find the first different -> higher is LCA
    return f[x][0];
}
void sol(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,0,0); // arbitrarily choose a root, here choose 1 as root
    for(int j=1;j<20;j++){
        for(int i=1;i<=n;i++){
            f[i][j] = f[f[i][j-1]][j-1];
        }// get all f
    }   
    // --- use lca(u,v) to get ---
}