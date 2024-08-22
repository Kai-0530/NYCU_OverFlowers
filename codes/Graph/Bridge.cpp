//for undirected graph, find bridge
const int N = 1e6+5;

vector<pair<int,int> > edge(N); //{u,v} ->remember to input
vector<pair<int,int> > g[N]; //{nxt,edge_id}
vector<int> bridge(N);
int dfn[N],vis[N],low[N],id; 
void tarjan(int now,int p){
    dfn[now]=id++;
    vis[now]=1;
    low[now]=dfn[now];
    for(auto [nxt,id]:g[now]){
        if(nxt==p) continue;
        if(vis[nxt]){
            low[now]=min(low[now],dfn[nxt]); //back edge!
        }
        else{
            tarjan(nxt,now);
            low[now]=min(low[now],low[nxt]);
            if(low[nxt]>dfn[now]){
                bridge[id]=1;
            }
        }
    }
}
signed main(){
    // construct
    for(int i=0;i<n;i++){
        dfn[i]=1e9;//reset
        low[i]=1e9;
        vis[i]=0;
    }
    id=0;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            tarjan(i,-1);
        }
    }
    // use
}