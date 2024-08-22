// i.e. bridge tree
// Remember to reset vis[]
map<int,int> compId;
vector<int> g2[N];
void dfs(int now,int p,int iid){
    vis[now]=1;
    compId[now]=iid;
    for(auto [nxt,id]:g[now]){
        if(bridge[id]) continue;
        if(nxt==p) continue;
        if(!vis[nxt]) dfs(nxt,now,iid);
    }
}
//////Then, in main()
    int iid=0;
    for(int i=0;i<n;i++) vis[i]=0;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            dfs(i,-1,iid);
            iid+=1;
        }
    }
    for(int i=0;i<m;i++){
        if(bridge[i]){
            auto [u,v] = edge[i];
            g2[compId[u]].pb(compId[v]);
            g2[compId[v]].pb(compId[u]);
        }
    }