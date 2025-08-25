struct SuffixArray{
    void countSort(vector <int> &pos, vector <int> &rank){
        int n = pos.size();
        vector <vector <int> > cnt(n);
        for(auto i : pos)  cnt[rank[i]].push_back(i);
        for(int i=0,idx=0;i<n;i++){
            for(auto x : cnt[i])
                pos[idx++] = x;
        }
    }
    void getSuffix(string s, vector <int> &pos, vector <int> &lcp){
        s += '$';
        int n = s.size();
        vector <int> rank(n);
        iota(pos.begin(), pos.end(), 0);
        sort(pos.begin(), pos.end(), [&](int a, int b){ return s[a] < s[b]; });
        // k = 0
        for(int i=0;i<n;i++){
            if(i == 0)
                rank[pos[i]] = 0;
            else
                rank[pos[i]] = rank[pos[i-1]] + (s[pos[i]] != s[pos[i-1]]); 
        }
        // k > 0
        vector <int> newRank(n);
        for(int k=0;(1<<k)<=n;k++){
            for(int i=0;i<n;i++)
                pos[i] = (pos[i] - (1 << k) % n + n) % n;
            countSort(pos, rank);
            newRank[pos[0]] = 0;
            for(int i=1;i<n;i++){
                pair<int,int> prev = {rank[pos[i-1]], rank[(pos[i-1]+(1<<k))%n]};
			    pair<int,int> now = {rank[pos[i]], rank[(pos[i]+(1<<k))%n]};
                newRank[pos[i]] = newRank[pos[i-1]] + (prev!=now);
            }
            rank = newRank;
        }
        // build lcp
        int k = 0;
        for(int i = 0;i < n;i++){
            int pi = rank[i];
            int j = pos[pi-1];
            while(i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
            lcp[pi] = k;
            k = max(0, k-1);
        }
    }
} sa;

/*
vector <int> pos, lcp;
sa.getSuffix(s, pos, lcp);
*/