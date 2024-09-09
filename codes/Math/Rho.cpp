#include <bits/stdc++.h>
using namespace std;

__int128 n;
__int128 gcd(__int128 a, __int128 b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

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

__int128 quick_pow(__int128 x, __int128 p, __int128 mod) { 
  __int128 ans = 1;
  while (p) {
    if (p & 1) ans = (__int128)ans * x % mod;
    x = (__int128)x * x % mod;
    p >>= 1;
  }
  return ans;
}

bool Miller_Rabin(__int128 p) {
  if (p < 2) return 0;
  if (p == 2) return 1;
  if (p == 3) return 1;
  __int128 d = p - 1, r = 0;
  while (!(d & 1)) ++r, d >>= 1; 
  for (int k = 0; k < 10; ++k) {
    __int128 a = (__int128)rand() % (p - 2) + 2;
    __int128 x = quick_pow(a, d, p);
    if (x == 1 || x == p - 1) continue;
    for (int i = 0; i < r - 1; ++i) {
      x = (__int128)x * x % p;
      if (x == p - 1) break;
    }
    if (x != p - 1) return 0;
  }
  return 1;
}

__int128 Pollard_Rho(__int128 x) {
  __int128 s = 0, t = 0;
  __int128 c = (__int128)rand() % (x - 1) + 1;
  __int128 step = 0, goal = 1;
  __int128 val = 1;
  for (goal = 1;; goal *= 2, s = t, val = 1) { 
    for (step = 1; step <= goal; ++step) {
      t = ((__int128)t * t + c) % x;
      __int128 ts;
      if(t >= s) ts = t-s;
      else ts = s-t;
      val = (__int128)val * ts % x;
      if ((step % 127) == 0) {
        __int128 d = gcd(val, x);
        if (d > 1) return d;
      }
    }
    __int128 d = gcd(val, x);
    if (d > 1) return d;
  }
}

set<__int128> st;
void fac(__int128 x){
    if(x<2) return;
    if(Miller_Rabin(x)){
        st.insert(x);
        return;
    }
    __int128 p = x;
    while(p>=x) p = Pollard_Rho(x);
    while((x%p) == 0) x /= p;
    fac(p); fac(x);
}

vector<__int128> v; // prime factors
set<__int128> allf; // factors
void dfs(__int128 res, __int128 now){
    auto it = allf.find(now);
    if(it != allf.end()) return;
    allf.insert(now);
    if(res < 2) return;
    for(__int128 i:v){
        if(res % i == 0){
            dfs(res / i, now * i);
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    n = read();
    __int128 N = (__int128)(n) * n;
    fac(n); // find all n's prime factor
    for(__int128 i:st) v.push_back(i);
    dfs(N, 1);
    // allf = all N's factors
    for(auto i:allf){
        print(i); cout<<endl;
    }
}