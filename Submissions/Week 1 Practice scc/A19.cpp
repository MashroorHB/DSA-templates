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

    ll* ts=gr.topologicalSort();
    gr.clearVis();
    gr.dfs(ts[0]);
    ll u=0;
    for(ll i=1; i<n; i++){
        if(!gr.vis[ts[i]]) u++;
    }
    if(u!=0) cout<< "NO\n";
    else{
        cout<< "YES\n";
        for(ll i=0; i<n; i++){
            cout<< ts[i]<< " ";
        }
        cout<< endl;
    }
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


