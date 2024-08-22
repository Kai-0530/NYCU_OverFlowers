const int N = 1e7+10;
const double Pi = acos(-1.0);
struct Complex{
    double x,y;
    Complex ( double xx=0, double yy=0){
        x=xx;
        y=yy;
    }
};
Complex a[N], b[N];
Complex operator + (Complex a, Complex b) { return Complex(a.x + b.x , a.y + b.y);}
Complex operator - (Complex a, Complex b) { return Complex(a.x - b.x , a.y - b.y);}
Complex operator * (Complex a, Complex b) { return Complex(a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x);}

int limit=1, h=0, rev[N];

void fft(Complex *A, int flag){
    for(int i=0; i<limit; i++){
        if(i<rev[i]){
            swap(A[i], A[rev[i]]);
        }
    }
    for(int len=1; len<limit; len<<=1){
        // len = 待合併區間的一半
        Complex Wn(cos(Pi/len), flag*sin(Pi/len));
        for(int R=len<<1, j=0; j<limit; j+=R){
            Complex w(1, 0); 
            for (int k = 0; k < len; k++, w = w * Wn) {
                Complex x = A[j + k], y = w * A[j + len + k]; 
                A[j + k] = x + y;
                A[j + len + k] = x - y;
            }
        }
    }
}

int main(){
	int n,m; // n,m次方
	cin>>n>>m;
    for(int i=0; i<=n; i++) cin>>a[i].x;
    for(int i=0; i<=m; i++) cin>>b[i].x;
    while(limit<=n+m){
        limit=limit<<1;
        h++;
    }
    for(int i=0; i<limit; i++){
        rev[i] = (rev[i>>1]>>1) | ((i&1)<<(h-1)); // bit reverse
    }
    fft(a, 1);
    fft(b, 1);//FFT
    for(int i=0; i<=limit; i++) a[i]=a[i]*b[i];
    fft(a, -1);//IFFT
    for(int i=0; i<=n+m; i++) cout<<(int)(a[i].x / limit + 0.5)<<" ";
}