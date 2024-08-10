const double eps = 1e-10, pi = acos(-1);
struct Circle{
    pdd o;
    double r;
}c;
vector<pdd> p;
int R, n, r;
pdd operator+(pdd a, pdd b){
    return {a.F + b.F, a.S + b.S};
}
pdd operator-(pdd a, pdd b){
    return {a.F - b.F, a.S - b.S};
}
pdd operator*(pdd a, double b){
    return {a.F * b, a.S * b};
} 
pdd operator/(pdd a, double b){
    return {a.F / b, a.S / b};
}
double operator*(pdd a, pdd b){
    return a.F * b.S -  a.S * b.F;
}
int judge(double a, double b){
    if (fabs(a-b) < eps) return 0;
    if (a < b) return -1;
    return 1;
}
pdd rotate(pdd a, double b){
    return {a.F*cos(b)+a.S*sin(b), -a.F*sin(b)+a.S*cos(b)};
}
double lens(pdd a, pdd b){
    double dx = b.F - a.F, dy = b.S - a.S;
    return sqrt(dx*dx + dy*dy);
}
pdd intersection(pdd p, pdd v, pdd q, pdd w){//求交點
    pdd u = p - q;
    double t = w*u/(v*w);
    return p + v * t;
}
pair<pdd, pdd> bisector(pdd a, pdd b){//求中垂線
    pdd p = (a + b) / 2.0;
    pdd v = rotate(b - a, pi / 2.0);
    return {p, v};
}
Circle circle(pdd a, pdd b, pdd c){ //三點求圓
    auto n = bisector(a, b), m = bisector(a, c);
    pdd o = intersection(n.F, n.S, m.F, m.S);
    double r = lens(o, a);
    return {o, r};
}
void solve(){
    p.clear();
    cin >> n;
    p.resize(n);
    for (int i = 1; i <= n; i++){
        cin >> p[i].F >> p[i].S;
    }
    random_shuffle(all(p));
    c = {p[0], 0};
    for(int i = 1; i <= n; i++){
        if (judge(c.r, lens(c.o, p[i])) == -1){
            c = {p[i], 0};
            for (int j = 0; j < i; j++){
                if (judge(c.r, lens(c.o, p[j])) == -1){
                    c = {(p[i] + p[j]) / 2.0, lens(p[i], p[j]) / 2.0};
                    for (int k = 0; k < j; k++){
                        if (judge(c.r, lens(c.o, p[k])) == -1){
                            c = circle(p[i], p[j], p[k]);
                        }
                    }
                }
            }
        }
    }
    //c: {圓心, 半徑}
    if (n == 1) c = {(p[0] + p[1]) / 2.0, 0};
    cout << setprecision(9) << fixed;
    cout << -c.o.F << " " << -c.o.S << endl;
}
