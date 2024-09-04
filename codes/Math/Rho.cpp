#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll max_factor, n;
ll gcd(ll a, ll b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

// read, print, cmp
__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }


ll quick_pow(ll x, ll p, ll mod) { 
  ll ans = 1;
  while (p) {
    if (p & 1) ans = (__int128)ans * x % mod;
    x = (__int128)x * x % mod;
    p >>= 1;
  }
  return ans;
}

bool Miller_Rabin(ll p) {
  if (p < 2) return 0;
  if (p == 2) return 1;
  if (p == 3) return 1;
  ll d = p - 1, r = 0;
  while (!(d & 1)) ++r, d >>= 1; 
  for (ll k = 0; k < 10; ++k) {
    ll a = rand() % (p - 2) + 2;
    ll x = quick_pow(a, d, p);
    if (x == 1 || x == p - 1) continue;
    for (int i = 0; i < r - 1; ++i) {
      x = (__int128)x * x % p;
      if (x == p - 1) break;
    }
    if (x != p - 1) return 0;
  }
  return 1;
}

ll Pollard_Rho(ll x) {
  ll s = 0, t = 0;
  ll c = (ll)rand() % (x - 1) + 1;
  int step = 0, goal = 1;
  ll val = 1;
  for (goal = 1;; goal *= 2, s = t, val = 1) { 
    for (step = 1; step <= goal; ++step) {
      t = ((__int128)t * t + c) % x;
      val = (__int128)val * abs(t - s) % x;
      if ((step % 127) == 0) {
        ll d = gcd(val, x);
        if (d > 1) return d;
      }
    }
    ll d = gcd(val, x);
    if (d > 1) return d;
  }
}

void fac(ll x) {
  if (x <= max_factor || x < 2) return;
  if (Miller_Rabin(x)) {            
    max_factor = max(max_factor, x); 
    return;
  }
  ll p = x;
  while (p >= x) p = Pollard_Rho(x);  
  while ((x % p) == 0) x /= p;
  fac(x), fac(p);  // 向下分解x和p
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        srand((unsigned)time(NULL));
        max_factor = 0;
        cin>>n;
        fac(n);
        if(max_factor==n){
            cout<<"Prime\n";
        }
        else{
            cout<<max_factor<<"\n";
        }
    }
}