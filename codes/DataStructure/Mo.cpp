// Mo's with update
// discretization + odd/even optimize
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+6;

int n,q,bks,sum,L,R;
vector<int> v(maxn), cnt(maxn);
vector<pair<int,int>> mod;
bool cmp(array<int,4> a, array<int,4> b){
    if(a[0] / bks == b[0] / bks){
        if(a[1] / bks == b[1] / bks){
            return a[2] < b[2];
        }
        else{
            return a[1] / bks < b[1] / bks;
        }
    }
    return (a[0] / bks) < (b[0] / bks);
}
void ADD(int x){
    if(++cnt[x] == 1) sum++;
}
void SUB(int x){
    if(--cnt[x] == 0) sum--;
}
void MOD(int x){
    auto [id, val] = mod[x];// mod_id = x
    if(id<=R && id>=L){
        ADD(val);
        SUB(v[id]);
    }
    swap(mod[x].second, v[id]);
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>q;
    bks = pow(n, (double)2/(double)3); // block = n^(1.5)
    for(int i=1;i<=n;i++) cin>>v[i];
    vector<array<int,4>> Q;
    vector<int> ans(q,-1);
    int tid = -1, l, r, T = -1;
    for(int i=0;i<q;i++){
        char c;
        cin>>c>>l>>r;
        if(c == 'Q'){
            Q.push_back({l, r, tid, i});
        }
        else{
            mod.push_back({l, r}); // replace (id=l) with (color=r)
            tid++;
        }
    }
    L = 1, R = 0;
    sort(Q.begin(),Q.end(),cmp);
    for(int i=0;i<Q.size();i++){
        auto [l,r,ti,ii] = Q[i];
        while(L > l) ADD(v[--L]);
        while(R < r) ADD(v[++R]);
        while(L < l) SUB(v[L++]);
        while(R > r) SUB(v[R--]);
        while(T < ti) MOD(++T);
        while(T > ti) MOD(T--);
        ans[ii] = sum;
    }
    for(int i:ans){
        if(i!=-1) cout<<i<<"\n";
    }
}
