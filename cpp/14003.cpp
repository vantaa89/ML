#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define MAX_N   1000007
int arr[MAX_N];
int d[MAX_N];       // d[k]: k번째 수로 끝나는 LIS의 최대 길이
int prev_idx[MAX_N];// prev_idx[i] = j : arr[i]로 끝나는 LIS의 뒤에서 두 번째 숫자가 arr[j]
vector<int> l, l_idx;      // l[k]: 길이 k인 LIS의 최소 끝 수
stack<int> st;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
	
    l.push_back(-2e9);
    l_idx.push_back(-1);
    d[0] = 0;

    for(int i = 1; i <= n; ++i){
        auto it = lower_bound(l.begin(), l.end(), arr[i]);  // *it >= arr[i]인 가장 작은 수. 즉, *(it-1) < arr[i]
        int length = it - l.begin() - 1;    // arr[i]보다 작은 수로 끝나는 LIS의 최대 길이
        prev_idx[i] = l_idx[length];
        if(length+1 < l.size()){
            l[length+1] = arr[i];
            l_idx[length + 1] = i;
        } else {
            l.push_back(arr[i]);
            l_idx.push_back(i);
        }
    }
	
	int ptr = -1;
	int ans = l.size() - 1;
	ptr = l_idx[ans];
	cout << ans << endl;
	while(ans--){
		st.push(arr[ptr]);
		ptr = prev_idx[ptr];
	}
	
    while(!st.empty()){
        cout << st.top() << " ";
        st.pop();
    }
	
    return 0;
}
