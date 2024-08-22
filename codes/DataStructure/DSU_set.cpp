/*
This DSU supports the following operations：
    1 x y, Union the sets containing x and q. If they are already in the same set, ignore.
    2 x y, Move x to the set containing y. If they are already in the same set, ignore.
    3 x, Return the number of elements and the sum of elements in the set containing x.
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+5;

int realIndex[maxn];
int p[maxn];
int ele[maxn];
int sum[maxn];
int cnt;

void init(int n){
    cnt = n + 1;
    for(int i=1;i<=n;i++){
        p[i] = i;
        ele[i] = 1;
        sum[i] = i;
        realIndex[i] = i;
    }
}

int find(int x){
    if(p[x] == x)
        return x;
    else 
        return p[x] = find(p[x]);
}

void merge(int x, int y){
    x = realIndex[x];
    y = realIndex[y];
    int px = find(x), py = find(y);
    if(px == py)
        return;
    p[px] = py;
    sum[py] += sum[px];
    ele[py] += ele[px];
}

void moveXToY(int x, int y){
    if(find(realIndex[x]) == find(realIndex[y]))
        return;
    sum[find(realIndex[x])] -= x;
    ele[find(realIndex[x])] -= 1;
    realIndex[x] = cnt++;
    sum[realIndex[x]] = x;
    ele[realIndex[x]] = 1;
    p[realIndex[x]] = realIndex[x];
    merge(x, y);
}

void output(int x){
    x = realIndex[x];
    x = find(x);
    cout << ele[x] << ' ' << sum[x] << endl;
}

signed main(){
    int n, q;
    while(cin >> n >> q){
        init(n);
        while(q--){
            int type;
            cin >> type;
            if(type == 1){
                int x, y;
                cin >> x >> y;
                merge(x, y);
            }
            else if(type == 2){
                int x, y;
                cin >> x >> y;
                moveXToY(x, y);
            }
            else{
                int x;
                cin >> x;
                output(x);
            }
        }
    }
}