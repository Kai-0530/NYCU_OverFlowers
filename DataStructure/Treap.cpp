#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node{ // support range reverse, range sum query
    node *l, *r;
    int key, val, sum, pri, size, rev;
    node(int k, int v) : l(0), r(0), key(k), val(v), sum(v), pri(rand()), size(1), rev(0){};
    void up();
    void down();
};

node *merge(node *a, node *b){
    if(!a || !b) return a ? a : b;
    if(a -> pri < b -> pri){
        a -> down();
        a -> r = merge(a -> r, b);
        a -> up();
        return a;
    }
    else{
        b -> down();
        b -> l = merge(a, b -> l);
        b -> up();
        return b;
    }
}

void split(node *o, node *&a, node *&b, int k){ // split by key
    if(!o)
        a = b = 0;
    else{
        o -> down();
        if(o -> key < k){
            a = o;
            split(o -> r, a -> r, b, k);
        }
        else{
            b = o;
            split(o -> l, a, b -> l, k);
        }
        o -> up();
    }
    
}

void insert(node *&root, int k, int v){
    node *a, *b;
    split(root, a, b, k);
    root = merge(a, merge(new node(k, v), b));
}

bool erase(node *&o, int k){  // erase T[k]
    if(!o) 
        return 0;
    if(o -> key == k){
        node *t = o;
        o = merge(o -> l, o -> r);
        delete t;
        return 1;
    }
    node *&t = k < o -> key ? o -> l : o -> r;
    if(erase(t, k)) return o -> up(), 1;
    else return 0;
}

void node :: up(){
    size = 1;
    sum = val;
    if(l) {
        //l -> down();
        size += l -> size;
        sum += l -> sum;
    }
    if(r) {
        //r -> down();
        size += r -> size; 
        sum += r -> sum;
    }
}

void node :: down(){
    if(rev){
        swap(l, r);
        if(l) l -> rev ^= 1;
        if(r) r -> rev ^= 1;
        rev = 0;
    }
}

inline int size(node *o){
    return o ? o -> size : 0;
}

int Rank(node *& root, int val){// Number of elements smaller than val.
    node *a, *b;
    split(root, a, b, val);
    int res = size(a);
    root = merge(a, b);
    return res;
}

void split2(node *o, node *&a, node *&b, int k){ // split by size
    if(!o) 
        a = b = 0;
    else{
        o -> down();
        if(k >= size(o -> l) + 1){
            a = o;
            int nk = k - (size(o -> l) + 1);
            split2(o -> r, a -> r, b, nk);
        }
        else{
            b = o;
            split2(o -> l, a, b -> l, k);
        }
        o -> up();
    }
}

node *kth(node *&root, int k){ // find T[k]
    node *a, *b, *c;
    split2(root, a, c, k);
    split2(a, a, b, k - 1);
    root = merge(a, merge(b, c));
    return b;
}

void reverse(node *&root, int l, int r){
    node *a, *b, *c;
    split2(root, a, b, l - 1);
    split2(b, b, c, r - l + 1);
    b -> rev ^= 1;
    root = merge(a, merge(b, c));
}

int query(node *&root, int l, int r){
    node *a, *b, *c;
    split2(root, a, b, l - 1);
    split2(b, b, c, r - l + 1);
    b -> down();
    int res = b -> sum;
    root = merge(a, merge(b, c));
    return res;
}

void update(node *&root, int pos, int x){ // let T[pos] = x
    erase(root, pos);
    insert(root, pos, x);
}

signed main(){
    node *T(nullptr);
    int n, q;
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int tmp;
        cin >> tmp;
        insert(T, i, tmp);
    }
    while(q--){
        int op;
        cin >> op;
        if(op == 1){ // update
            int pos, x;
            cin >> pos >> x;
            update(T, pos, x);
        }
        else{ // query
            int l, r;
            cin >> l >> r;
            cout << query(T, l, r) << '\n';
        }
    }
}