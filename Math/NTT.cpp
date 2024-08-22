const int N = 1e7+10;
const int P = 998244353, G = 3, Gi = 332748118;// primitive root = 3, Gi = mod inverse of 3

int fastpow(int x,int p){
    int sum = 1;
    while(p){
        if(p&1) sum = sum*x%P;
        x = x*x%P;
        p = p>>1;
    }
    return sum;
}

int a[N], b[N], limit=1, h=0, rev[N];
inline void NTT(int *A, int flag) {
	for(int i = 0; i < limit; i++) 
		if(i < rev[i]) swap(A[i], A[rev[i]]);
	for(int len = 1; len < limit; len <<= 1){	
		int Wn = fastpow( flag == 1 ? G : Gi , (P - 1) / (len << 1));
		for(int j = 0; j < limit; j += (len << 1)){
			int w = 1;
			for(int k = 0; k < len; k++) {
                int x = A[j + k], y = w * A[j + k + len] % P;
                A[j + k] = (x + y) % P,
                A[j + k + len] = (x - y + P) % P;
                w = (w * Wn) % P;
            }
		}
	}
}

signed main(){
    int n,m;
    cin>>n>>m; // n,m次方
    for(int i=0; i<=n; i++){
        cin>>a[i];
        a[i]=(a[i] + P) % P; 
    }
    for(int i=0; i<=m; i++){
        cin>>b[i];
        b[i]=(b[i] + P) % P; 
    }
    while(limit<=n+m){
        limit=limit<<1;
        h++;
    }
    for(int i=0; i<limit; i++){
        rev[i] = (rev[i>>1]>>1) | ((i&1)<<(h-1));
    }
    NTT(a, 1);
    NTT(b, 1);
    for(int i=0; i<=limit; i++) a[i]=a[i]*b[i]%P;
    NTT(a, -1);
    
    int inv = fastpow(limit, P - 2);
    for(int i=0; i<=n+m; i++){
        cout<<(a[i]*inv)%P << " ";
    }
}