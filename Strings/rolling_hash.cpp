const int N = 2000; // string size
int X = 1000000007, P = 4000000007; 
// other primes : 8298176713 5119240589 3735751997 3218996237...
int s[N], p[N]; // if hash兩次 -> 開兩個s,p

void Hash(string& str){
    s[0] = str[0];
    p[0] = 1;
    for(int i=1; i<str.size(); i++){
        s[i] = (s[i-1]*X + str[i])%P;
        p[i] = (p[i-1]*X) % P;
    }
    return;
}
int hash_i(int a,int b){
    if(!a) return s[b];
    int tmp = s[b] - s[a-1]*p[b-a+1]; // calculate H[a:b]
    tmp=tmp%P;
    if(tmp<0) return tmp+P;
    return tmp;
}

signed main(){
    // Hash to generate s and p
    // hash_i to calculate s[a:b]
    string s;
    cin>>s;
    Hash(s);
    cout<<hash_i(0,2)<<" "<<hash_i(3,5);
}