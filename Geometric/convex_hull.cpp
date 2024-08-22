template<typename T>
pair<T, T> operator+(pair<T, T> a, pair<T, T> b){
    return make_pair(a.first + b.first, a.second + b.second);
}

template<typename T>
pair<T, T> operator-(pair<T, T> a, pair<T, T> b){
    return make_pair(a.first - b.first, a.second - b.second);
}

template<typename T>
pair<T, T> operator*(pair<T, T> a, T b){
    return make_pair(a.first * b, a.second * b);
}

template<typename T>
pair<T, T> operator/(pair<T, T> a, T b){
    return make_pair(a.first / b, a.second / b);
}

template<typename T>
T dot(pair<T, T> a, pair<T, T> b){
    return a.first * b.first + a.second * b.second;
}

template<typename T>
T cross(pair<T, T> a, pair<T, T> b){
    return a.first * b.second - a.second * b.first;
}

template<typename T>
T abs2(pair<T, T> a){
    return a.first * a.first + a.second * a.second;
}

void sol(){
    int n;
	cin>>n;
	if(n==0){
		cout<<"NO"<<endl; return;
	}
    vector<pair<int,int> > v(n);
    for(int i=0;i<n;i++) cin>>v[i].first>>v[i].second;
    sort(v.begin(), v.end());
    stack<pair<int,int> > st;

    for(int t=0;t<2;t++){
        int sz = st.size();
        for(int i=0;i<n;i++){
            if(!i) st.push(v[i]);
            else{
                if(v[i]==v[i-1]) continue;
                while(st.size()-sz >= 2){
                    auto P = st.top();
                    st.pop();
                    if(cross(P-st.top(), v[i]-P) > 0){
                        st.push(P); 
                        break;
                    }
                }
                st.push(v[i]);
            }
        }
        if(st.size()>1) st.pop(); 
        reverse(v.begin(),v.end());
    }
    vector<pair<int,int> > ans;
    cout<<st.size()<<'\n'; //stack 順時針方向存
    while(!st.empty()){
        ans.pb(st.top());
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    for(auto ii:ans) cout<<ii.first<<" "<<ii.second<<'\n'; // 逆時針方向輸出
}