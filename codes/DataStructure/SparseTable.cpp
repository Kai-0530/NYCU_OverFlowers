const int MAXN = 5e5 + 5;
const int lgN = 20;

struct SP{
    vector <int> Sp[lgN];
    void build(int n, int *a){
        for(int i=0;i<n;i++) 
            Sp[0].push_back(a[i]);
        for(int h=1;h<lgN;h++){
            int len = (1 << (h - 1)), i = 0;
            for(; i + len < n; i++)
                Sp[h].push_back(max(Sp[h-1][i], Sp[h-1][i+len]));
            for(; i < n; i++)
                Sp[h].push_back(Sp[h-1][i]);
        }
    }    
    int query(int l, int r){
        int lg = __lg(r - l + 1);
        int len = (1 << lg);
        return max(Sp[lg][l], Sp[lg][r - len + 1]);
    }
};