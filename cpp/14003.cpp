#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

#define MAX_N   1000001
int arr[MAX_N];
int d[MAX_N];
int prev_idx[MAX_N];


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    vector<int> l;
    vector<int> l_idx;
    // l[k]: 길이 k인 LIS 중 끝 수가 가장 작은 것의 끝 수
    // l_idx[k]: 그 때 끝 수의 index

    l.push_back(0);
    int last = 0;
    for(int i = 1; i <= n; ++i){
        // arr[i]보다 작은 끝 수를 가졌으면서, 가장 긴 LIS의 길이?
        auto it = lower_bound(l.begin(), l.end(), arr[i]);      // it - 1
        if (it == l.end()){
            l.push_back(arr[i]);
            l_idx.push_back(i);
            last = i;
            prev_idx[i] = l_idx[l_idx.size()-2];
        } 
        else {
            l[it - l.begin()] = arr[i];
            l_idx[it - 1 - l.begin()] = i;
            prev_idx[i] = it - l.begin() - 1;
        }
    }

    int ans = l.size() - 1;
    cout << ans << endl;
    int ptr = last;
    stack<int> out;
    while(ans--){
        out.push(arr[ptr]);
        ptr = prev_idx[ptr];
    }
    while(!out.empty()){
        cout << out.top() << " ";
        out.pop();
    }
    return 0;
}
