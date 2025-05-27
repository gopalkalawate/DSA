#include<bits/stdc++.h>
using namespace std;
#define ll long long
// to find the least common ancestor of all elements

void dfs(int u,int par,vector <vector<int>> &tree,vector <vector<int>> &LCA,vector <int> &levels){
    LCA[u][0] = par;
    for(int v : tree[u]){
        if(v==par){
            continue;
        }
        levels[v] = levels[u] + 1;
        dfs(v,u,tree,LCA,levels);
    }
}

int findLCA(int u,int v,int maxN,vector <int> &levels,vector <vector<int>> &LCA){
    if(levels[u]>levels[v]) swap(u,v);
    int d = levels[v] - levels[u];
    while(d>0){
        int jump = log2(d);
        v = LCA[v][jump];
        d -= (1<<jump);
    }// we bring both a and b to the same level 
    if(u==v){
        return v;
    }

    // now we find the lca

    for(int i=maxN;i>=0;i--){
        if(LCA[u][i]!=-1 && LCA[u][i]!=LCA[v][i]){
            u = LCA[u][i];
            v = LCA[v][i];
        }
    }
    return LCA[u][0];
}

int main(){
    int n,q;cin>>n>>q;
    vector <vector<int>> tree(n+1);
    vector <int> levels(n+1,0);
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    int maxN = log2(n); // no of bits ke jiske liye lifting karna ho
    vector <vector<int>> LCA(n+1,vector <int> (maxN + 1,-1));
    dfs(1,-1,tree,LCA,levels);

    // for(int i=1;i<=n;i++){
    //     cout<<levels[i]<<' ';
    // }

    for(int i=1;i<=maxN;i++){
        for(int j=1;j<=n;j++){
            int i_minus_one_parent = LCA[j][i-1];
            if(i_minus_one_parent!=-1){
                LCA[j][i] = LCA[i_minus_one_parent][i-1];
            }
        }
    }// we have got it , now we will be given 2 edges we have to find the LCA of the two nodes

    while(q--){
        ll u,v;cin>>u>>v;
        cout<<findLCA(u,v,maxN,levels,LCA)<<endl;
    }

}