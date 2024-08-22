//#define pdd (double/int)
int cross(pdd a, pdd b){
    return a.first*b.second - a.second*b.first;
}

pdd operator-(pdd a, pdd b){
    return {a.first - b.first, a.second - b.second};
}

double operator*(pdd a, pdd b){
    return a.first * b.second -  a.second * b.first;
}

// ps是所有的點, 要去重!!!
vector<pdd> convexHull(vector<pdd>& ps) {
    sort(all(ps));
    vector<pdd> hull;
    if (ps.size() <= 2) {
        return ps;
    }
    for (int i = 0; i < 2; i++) {
        int s = hull.size();
        for (pdd p : ps) {
            while (hull.size() - s >= 2 && cross(hull.back() - hull[hull.size() - 2], p - hull[hull.size() - 2]) < 1e-10) {
                hull.pop_back();
            }
            hull.pb(p); //push_back
        }
        hull.pop_back();
        reverse(all(ps));
    }
    return hull;
}
