// range upd (+k) and query sum
#include <bits/stdc++.h>
#define int long long int
using namespace std;
const int N=1e5+10;
struct node{
    int sum;
    int l,r;
    int tag;
}tr[N*4];
int a[N];
inline void pushup(int x){
    tr[x].sum=tr[2*x].sum+tr[2*x+1].sum;//pushup操作
}
inline void pushudown(int x){
    if(tr[x].tag){
        tr[2*x].tag+=tr[x].tag,tr[2*x+1].tag+=tr[x].tag;
        tr[2*x].sum+=tr[x].tag*(tr[2*x].r-tr[2*x].l+1);
        tr[2*x+1].sum+=tr[x].tag*(tr[2*x+1].r-tr[2*x+1].l+1);
        tr[x].tag=0;
    }
}
void build(int x,int l,int r){
    tr[x].l=l,tr[x].r=r,tr[x].tag=0;
    if(l==r){
        tr[x].sum=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(2*x,l,mid),build(2*x+1,mid+1,r);
    pushup(x);
}
int query(int x,int l,int r){
    if(l<=tr[x].l&&r>=tr[x].r) return tr[x].sum;
    pushudown(x);
    int mid=(tr[x].l+tr[x].r)/2,sum=0;
    if(l<=mid) sum+=query(x*2,l,r);
    if(r>mid) sum+=query(x*2+1,l,r);
    return sum; 
}
void update(int now,int l,int r,int k){
    if(l<=tr[now].l&&r>=tr[now].r){
        tr[now].sum+=k*(tr[now].r-tr[now].l+1);
        tr[now].tag+=k; // 先改再標記
    }
    else{
        pushudown(now);
        int mid=(tr[now].l+tr[now].r)/2;
        if(l<=mid) update(now*2,l,r,k);
        if(r>mid) update(now*2+1,l,r,k);
        pushup(now);
    }
}
int n,q;
signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(q--){
        int l,r,k,c;
        cin>>c>>l>>r;
        if(c==1){
            cin>>k;
            update(1,l,r,k);
        }
        else cout<<query(1,l,r)<<endl;
    }
}