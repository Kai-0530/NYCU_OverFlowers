int f[100]; // state, reset to -1

int sg(int x) {
    if (f[x] != -1) return f[x];
    unordered_set<int> S;
    if (x >= 1) S.insert(sg(x - 1)); // all sub-states (suppose x can be x-1, x-2, 0)
    if (x >= 2) S.insert(sg(x - 2));
    if (x >= 3) S.insert(sg(0));
    for (int i = 0;; i++) {
        if (!S.count(i)) return f[x] = i;
    }
}