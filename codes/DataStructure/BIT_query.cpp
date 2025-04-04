// N = max value, LOGN = log(N)
int bit_search(int v){
	int sum = 0, pos = 0;
	for(int i=LOGN; i>=0; i--){
		if(pos + (1 << i) < N and sum + bit[pos + (1 << i)] < v){
			sum += bit[pos + (1 << i)];
			pos += (1 << i);
		}
	}
    // may use bit_query to check:
    // if(que(pos+1) < v) return 1e9;
	return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
}