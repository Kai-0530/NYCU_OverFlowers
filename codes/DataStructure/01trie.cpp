// for xor
const int N = 1e5+5;
int tot,trie[41*N][2],n; // need reset tot, trie
int find(int x){
    int p=0,sum=0;
    for(int i=40;i>=0;i--){
        int id=(x>>i)&1;
        if(trie[p][id^1]){ // here, choose id^1
            sum=sum*2+1;
            p=trie[p][id^1];
        }
        else{
            sum=sum*2; // here, choose id
            p=trie[p][id];
        }
    }
    return sum;
}
// fixed:
void insert(int x){
    int p=0;
    for(int i=40;i>=0;i--){
        int id=(x>>i)&1;
        if(!trie[p][id]) trie[p][id]=++tot;
        p=trie[p][id];
    }
}
