#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;

#define MAX_N   100000
#define LOG     17

int n, log_n;
vector<int> adj[MAX_N];
int depth[MAX_N];
int parent[MAX_N][LOG];


void dfs(int node, int height){
    depth[node] = height;
    for(auto next: adj[node]){
        if(depth[next] == -1){
            parent[next][0] = node;
            dfs(next, height + 1);
        }
    }
}

void set_parent(){
    fill(depth, depth + MAX_N, -1);
    dfs(0, 0);
    for(int j = 1; j <= log_n; ++j){
        for(int i = 0; i < n; ++i){
            parent[i][j] = parent[parent[i][j-1]][j-1];
        }
    }
}


int find_lca(int u, int v){
    if(depth[u] > depth[v]){
        swap(u, v);
    }
    for(int j = log_n; j >= 0; --j){
        if(depth[v] - depth[u] >= (1 << j)){
            v = parent[v][j];
        }        
    }

    if (u == v) return u;
    for(int j = log_n; j >= 0; --j){
        if (parent[u][j] != parent[v][j]){
            u = parent[u][j];
            v = parent[v][j];
        }
    }
    return parent[u][0];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    cin >> n;
    log_n = int(log2(n));
    int u, v, w, k;
    for(int i = 0; i < n-1; ++i){
        cin >> u >> v;
        --u;--v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    set_parent();
    int m;
    cin >> m;
    while(m--){
        cin >> u >> v;
        --u;--v;
        cout << find_lca(u, v)+1 << endl;
    }
    return 0;
}