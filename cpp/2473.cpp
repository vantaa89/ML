#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N   5000


int main(){
    int n;
    long long num;
    cin >> n;
    vector<long long> pos, neg;
    for(int i = 0; i < n; ++i){
        cin >> num;
        if(num >= 0) pos.push_back(num);
        else neg.push_back(-num);
    }
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end());

    long long min_abs = 2e12;
    long long candid[3];

    if(pos.size() >= 3){
        if(min_abs > abs(pos[0] + pos[1] + pos[2])){
            min_abs = abs(pos[0] + pos[1] + pos[2]);
            candid[0] = pos[0];
            candid[1] = pos[1];
            candid[2] = pos[2];
        }
    }
    if(neg.size() >= 3){
        if(min_abs > abs(neg[0] + neg[1] + neg[2])){
            min_abs = abs(neg[0] + neg[1] + neg[2]);
            candid[0] = -neg[0];
            candid[1] = -neg[1];
            candid[2] = -neg[2];
        }
    }
    
    

    for(long long x: pos){
        for(int i = 0; i < neg.size(); ++i){
            long long y = neg[i];
            auto it = lower_bound(neg.begin(), neg.end(), x-y);
            if(min_abs > abs(x-y-(*it)) && it-neg.begin() != i){
                min_abs = abs(x-y-(*it));
                candid[0]=x;
                candid[1]=-y;
                candid[2]=-(*it);
            }
            if (it > neg.begin()){
                if(min_abs > abs(x-y-(*(it-1))) && it-1-neg.begin() != i){
                    min_abs = abs(x-y-(*(it-1)));
                    candid[0]=x;
                    candid[1]=-y;
                    candid[2]=-(*(it-1));
                }
            }
        }
    }
    
    for(long long x: neg){
        for(int i = 0; i < pos.size(); ++i){
            long long y = pos[i];
            auto it = lower_bound(pos.begin(), pos.end(), x-y);
            if(min_abs > abs(x-y-(*it)) && it-pos.begin() != i){
                min_abs = abs(x-y-(*it));
                candid[0]=-x;
                candid[1]=y;
                candid[2]=(*it);
            }
            if (it > pos.begin()){
                if(min_abs > abs(x-y-(*(it-1)))  && it-1-pos.begin() != i){
                    min_abs = abs(x-y-(*(it-1)));
                    candid[0]=-x;
                    candid[1]=y;
                    candid[2]=*(it-1);
                }
            }
        }
    }


    sort(candid, candid+3);
    for(int i = 0; i < 3; ++i){
        cout << candid[i] << " ";
    }

    return 0;
}