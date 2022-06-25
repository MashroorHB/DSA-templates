#include<bits/stdc++.h>
#include "Graph.h"
using namespace std;
typedef int ll;

int main(){
    ll n, m; cin>> n>> m;
    Graph gr(n,true,true);
    ll g, h;
    for(ll i=0; i<m; i++){
        cin>> g>> h;
        if(g==0) g=n;
        if(h==0) h=n;
        gr.addEdge(g,h,false);
    }


    vector< vector<ll> > rt=gr.SCC();
    ll par[n+1];
    for(ll i=0; i<rt.size(); i++){
        for(ll j=0; j<rt[i].size(); j++){
            par[rt[i][j]]=i+1;
        }
    }
    Graph tarjan(rt.size());
    for(ll i=1; i<=n; i++){
        for(ll j=0; j<gr.adj[i].size(); j++){
            if(par[i]!=par[gr.adj[i][j].x]){
                tarjan.addEdge(par[i],par[gr.adj[i][j].x],false);
            }
        }
    }
    ll* ts=tarjan.topologicalSort();
    tarjan.clearVis();
    tarjan.dfs(ts[0]);
    ll u=0;
    for(ll i=1; i<rt.size(); i++){
        if(!tarjan.vis[ts[i]]) u++;
    }
    (u==0)? cout<< (rt[ts[0]-1][0])%n<< endl : cout<< "-1\n";
}

/*
4 5
0 1
1 2
0 2
1 3
3 2


3 3
0 1
1 2
2 0
*/


