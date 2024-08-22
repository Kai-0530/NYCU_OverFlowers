struct Per_seg{
    int l, r, m;
    int v = 0;
    Per_seg *ln = nullptr, *rn = nullptr;
    Per_seg(int _l, int _r) : l(_l), r(_r), m((_l + _r) >> 1) {}
    void build(){
        if (l != r - 1)
        {
            ln = new Per_seg(l, m);
            rn = new Per_seg(m, r);
            ln->build();
            rn->build();
        }
    }
    void upd(int tar, int value){
        if (tar == l && tar == r - 1){
            v = value;
            return;
        }
        else{
            int m = (l + r) >> 1;
            if (tar < m){
                ln = new Per_seg(*ln);
                ln->upd(tar, value);
            }
            else{
                rn = new Per_seg(*rn);
                rn->upd(tar, value);
            }
            v = ln->v + rn->v;
        }
    }
    int query(int ll, int rr){
        if (l == ll && r == rr){
            return v;
        }
        else{
            if (m >= rr){
                return ln->query(ll, rr);
            }
            else if (m <= ll){
                return rn->query(ll, rr);
            }
            else{
                return ln->query(ll, m) + rn->query(m, rr);
            }
        }
    }
};

signed main(){
    int n, q; // n = array size, q = query times
    cin>>n>>q;
    vector<Per_seg *> tr;
    tr.push_back(new Per_seg(0, n));
    tr[0]->build();
    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        tr[0]->upd(i, a); // init ver.0, 0-based!
    } // build done
    // Set the value a in array k to x: tr[k]->upd(a, x);
    // Sum of values in range [a,b) in array k: tr[k]->query(l, r)
    // []? [)?
    // Create a copy of array k: tr.push_back(new Per_seg(*tr[k]))
}