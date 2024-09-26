vector<int> Failure(const string &s){
    // initialize the failure function
    vector <int> f(s.size(), 0);
    int k = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        while (k > 0 && s[i] != s[k]) k = f[k - 1];
        if (s[i] == s[k]) ++k;
        f[i] = k;
    }
    return f;
}

vector <int> Matching(const string &s, const string &t){
    // return 0-indexed occurrence of t in s
    // O(N + M)
    vector <int> f = Failure(t);
    int l = 0; // for the index of s
    int r = 0; // for the index of t(pattern)
    vector <int> res ;
    while(l < s.size()){
        if(s[l] == t[r]){
            l++;
            r++;
            if(r == t.size()){
                res.push_back(l - t.size());
                r = f[r-1];
            }
        }
        else{
            if(r == 0){
                l++;
            }
            else{
                r = f[r-1];
            }
        }
    }
    return res;
}