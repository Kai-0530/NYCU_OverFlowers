#include <bits/stdc++.h>
#define int long long
using namespace std;

int QuickPow(int base, int exponent, int mod){
    if(exponent == 0) 
        return 1;
    if(exponent == 1)
        return base;
    if(exponent % 2)
        return QuickPow(base, exponent - 1, mod) * base % mod;
    int tmp = QuickPow(base, exponent / 2, mod);
    return tmp * tmp % mod;
}

bool RabinMiller(int d, int n){
    int a = 2 + rand() % (n - 2);
    if(QuickPow(a, n - 1, n) != 1)
        return false;
    int cur = QuickPow(a, d, n);
    int nx;
    while(d != n - 1){
        nx = (cur * cur) % n;
        d *= 2;
        if(cur != 1 && cur != n - 1){
            if(nx == 1)
                return false;
        }
        cur = nx;
    }
    return true;
}

bool isPrime(int n, int k){
    if(n <= 1)
        return false;
    if(n <= 3)
        return true;
    if(n == 4)
        return false;
    if((n - 1) % 6 != 0 && (n + 1) % 6 != 0)
        return false;
    int d = n - 1;
    int r = 0;
    while(d % 2 == 0){
        d /= 2;
        r ++;
    }
    for(int i=0;i<k;i++){
        if(!RabinMiller(d, n))
            return false;
    }
    return true;
}

signed main(){
    int n;
    while(cin >> n){
        if(isPrime(n, 5)) // 預設k = 5
            cout << "質數" << endl;
        else
            cout << "非質數" << endl;
    }
}