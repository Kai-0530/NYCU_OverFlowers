#include<bits/stdc++.h>
using namespace std;
struct Per_seg{
    int id,nn;
    vector<int> ln,rn,val,root;
    Per_seg(int n, vector<int> &arr) : nn(n), id(0){
        root.resize(1);
        ln.resize(32*n);
        rn.resize(32*n);
        val.resize(32*n);
        root[0] = build(0, nn-1, arr);
    }
    int build(int l, int r, vector<int> &arr){
        int rt = ++id, mid = (l+r)>>1;
        if(l==r){
            val[rt] = arr[l];
            return rt;
        }
        ln[rt] = build(l, mid, arr);
        rn[rt] = build(mid+1, r, arr);
        val[rt] = val[ln[rt]] + val[rn[rt]]; // pull
        return rt;
    }
    int update(int pre_id, int l, int r, int pos, int v){
        int rt = ++id, mid = (l+r)>>1;
        ln[rt] = ln[pre_id];
        rn[rt] = rn[pre_id];
        val[rt] = val[pre_id];
        if(l==r){
            val[rt] = v;
            return rt;
        }
        if(pos<=mid) ln[rt] = update(ln[pre_id], l, mid, pos, v);
        else rn[rt] = update(rn[pre_id], mid+1, r, pos, v);
        val[rt] = val[ln[rt]] + val[rn[rt]]; // pull
        return rt;
    }
    int query2(int o, int l, int r, int ql, int qr){
        if(l>=ql && r<=qr) return val[o];
        int mid = (l+r)>>1;
        if(qr<=mid) return query2(ln[o], l, mid, ql, qr);
        else if(ql>mid) return query2(rn[o], mid+1, r, ql, qr);
        return query2(ln[o], l, mid, ql, qr) + query2(rn[o], mid+1, r, ql, qr);
    }
    // ---for outer---
    int clone(int ver){
        int rt = ++id;
        ln[rt] = ln[root[ver]];
        rn[rt] = rn[root[ver]];
        val[rt] = val[root[ver]];
        root.push_back(rt);
        return rt;
    }
    void point_update(int ver, int pos, int newVal) {
        int newRoot = update(root[ver], 0, nn-1, pos, newVal);
        // root.push_back(newRoot); // copy
        root[ver] = newRoot; // replace
    }
    int range_query(int ver, int l, int r){
        // root.push_back(root[ver]); // copy
        return query2(root[ver], 0, nn-1, l, r);
    }
};
/*
0-indexed!!
Per_seg seg(n, arr); - build
*/
