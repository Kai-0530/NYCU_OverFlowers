#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
template<typename T> using rbt = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int main(){
    rbt<int> t; //declare
}

/*
不支援重複值 (需要的話可用左推+值來處理)
支援set, map之操作
find_by_order(k) ：像陣列一樣回傳第 k 個值。(0-based, pointer)
order_of_key(k) ：回傳 k 是集合裡第幾大。(0-based)

T 資料型別
null_type //當作 map 使用的時候要對應什麼資料型態，
		  //要當作 set 就用 null_type
less<T>	// key value 要用什麼方式比較
*/