// range upd (+k) and query sum
#include<bits/stdc++.h>
#define int long long int
using namespace std;
const int maxn = 2e5+5;

struct SegTree{
    // only need to revise pull & addTag
    int sum[maxn*4], tag[maxn*4];
    void init(int n){
        for(int i=0; i<=n*4; i++){
            sum[i] = 0;
            tag[i] = 0;
        }
    }
    int L(int x){
        return (x<<1);
    }
    int R(int x){
        return (x<<1|1);
    }
    void pull(int id){
        sum[id] = sum[L(id)] + sum[R(id)];
    }
    void addTag(int id, int l, int r, int k){
        tag[id] += k;
        int len = r-l+1;
        sum[id] += k*len;
    }
    void pushTag(int id, int l, int r){
        int mid = (l+r)>>1;
        addTag(L(id), l, mid, tag[id]);
        addTag(R(id), mid+1, r, tag[id]);
        tag[id] = 0;
    }
    void build(int id, int l, int r, vector<int> &v){
        if(l == r){
            sum[id] = v[l];
            tag[id] = 0;
            return;
        }
        int mid = (l+r)>>1;
        build(L(id), l, mid, v);
        build(R(id), mid+1, r, v);
        pull(id);
    }
    void range_update(int id, int l, int r, int ll, int rr, int val){
        if(ll <= l && r <= rr){
            addTag(id, l, r, val);
            return;
        }
        pushTag(id, l, r);
        int mid = (l+r)>>1;
        if(ll <= mid) range_update(L(id), l, mid, ll, rr, val);
        if(mid < rr) range_update(R(id), mid+1, r, ll, rr, val);
        pull(id);
    }
    int range_query(int id, int l, int r, int ll, int rr){
        if(l>=ll && r<=rr) return sum[id];
        pushTag(id, l, r);
        int mid = (l+r)>>1, res=0;
        if(ll<=mid) res += range_query(L(id), l, mid, ll, rr);
        if(mid<rr) res += range_query(R(id), mid+1, r, ll, rr);
        return res;
    }
}segtree;
// segtree.init(n);
// vector<int> v(n+1); (indexed at 1!!!)
// segtree.build(1, 1, n, v);
// range update + range query