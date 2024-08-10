//記得先定義叉積與減
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
                hull.ppb();
            }
            hull.pb(p);
        }
        hull.ppb();
        reverse(all(ps));
    }
    return hull;
}
