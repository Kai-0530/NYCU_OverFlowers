const int N = 2005;
int low[N],dfn[N],color[N],ins[N]; //要開兩倍大
// color[x] 是 x 所在的 scc 的topo逆序。
vector<int> g[N];
int dfsClock,sccCnt;
stack<int> stk;
void tarjan(int u) {
    low[u] = dfn[u] = ++dfsClock;
    stk.push(u); ins[u] = true;
    for (const auto &v : g[u]) {
        if (!dfn[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
        else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++sccCnt;
        do {
            color[u] = sccCnt;
            u = stk.top(); stk.pop(); ins[u] = false;
        } while (low[u] != dfn[u]);
    }
}

signed main(){
    g[i].pb(j); // i->j
    
    for (int i = 1; i <= (n << 1); ++i) if (!dfn[i]) tarjan(i);  // run tarjan, 注意0~2n-1 or 1~2n
    
    for(int i=1;i<=n;i++){
        if(color[i] == color[i+n]){
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
    // 找環 注意建邊方法是(i,i+1) or (i,i+n)

    for(int i=1;i<=n;i++){
        if(color[i] < color[i+n]){
            cout<<1<<" ";
        }
        else cout<<0<<" ";
    }
    // 構造解 (注意是0~n-1還是1~n)
}