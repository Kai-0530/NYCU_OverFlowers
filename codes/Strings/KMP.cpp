vector<int> Failure(const string &s){
    // initialize the failure function
    vector <int> f(s.size());
    for(int i=0;i<s.size();i++)
        f[i] = -1;
    for(int i=1;i<s.size();i++){
        if(f[i-1] != -1){
            if(s[i] == s[f[i-1]+1]){
                f[i] = f[i-1] + 1;
            }
            else {
                if(s[i] == s[0]){
                    f[i] = 0;
                }
            }
        }
        else{
            if(s[i] == s[0]){
                f[i] = 0;
            }
        }
    }
    return f;
}

vector <int> Matching(const string &s, const string &t){
    // return 0-indexed occurrence of t in s
    // O(N + M)
    vector <int> f = Failure(t);
    int l = 0; // for the index of s
    int r = 0; // for the index of t(pattern)
    vector <int> res;
    while(l < s.size()){
        if(s[l] == t[r]){
            l++;
            r++;
            if(r == t.size()){
                res.push_back(l - t.size());
                r = f[r-1] + 1;
            }
        }
        else{
            if(r == 0){
                l++;
            }
            else{
                r = f[r-1] + 1;
            }
        }
    }
    return res;
}