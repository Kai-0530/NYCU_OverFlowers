// Tarjan (offline, O(n + m))
void dfs(int now, int p, int dep){
    d[now] = dep; // d[i] = depth of i, be careful about "root should set to 0/1"
    for(int nxt:g[now]){
        if(nxt==p) continue;
        dfs(nxt, now, dep+1);
        connect(now,nxt); // connect son "to" its parent
        vis[nxt] = 1;
    }
    // Deal with query
    for(auto i:q[now]){
        int nxt = i.first; // query has {now,nxt}
        int id = i.second; // query_id
        if(vis[nxt]){
            qans[id] = find_root(nxt);
        }
    }
}