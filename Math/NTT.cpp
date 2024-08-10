int n, k;
int fp(int a, int m){
    int res = 1;
    while (m){
        if (m & 1) res = res * a % p;
        a = a * a % p;
        m >>= 1;
    }
    return res;
}
int rev[2000005], d[2000005];
void init(int len){
    for (int i = 1; i < len; i++){
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1) rev[i] |= len >> 1;
    }
}
void ntt(int a[], int len, int inv){
    for  (int i = 0; i < len; i++){
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int h = 2; h <= len; h <<= 1){
        int gn = fp(inv == 1 ? g : gi, (p - 1) / h);
        for (int j = 0; j < len; j += h){
            int gk = 1;
            for (k = j; k < j + h / 2; k++){
                int x = a[k], y = gk * a[k + h / 2] % p;
                a[k] = (x + y) % p;
                a[k + h / 2] = (x + p - y) % p;
                gk = gk * gn % p;
            }
        }
    }
    if (inv == -1){
        int ki = fp(len, p - 2);
        for (int i = 0; i < len; i++){
            a[i] = a[i] * ki % p;
        }
    }
}
