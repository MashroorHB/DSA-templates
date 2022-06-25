#include<bits/stdc++.h>
#include "graph.h"
using namespace std;
typedef int ll;

#define pll pair<ll,ll>
#define pld pair<ll,double>
#define pdl pair<double,ll>
#define mp make_pair
#define x first
#define y second

bool adj[1009][1009][2];
bool vis[1009][2];

void clearVis(ll n){
    for(int i=0; i<=n; i++){
        vis[i][0]=false;
        vis[i][1]=false;
    }
};

void dfs(int v, int n, int gen)
{
    vis[v][gen] = true;
    for (int i=1; i <=n; i++){
        if(adj[v][i][gen] && !vis[i][gen]){
            dfs(i,n,gen);
        }
    }
    return;
}

bool isConnected(ll n){
    clearVis(n);
    dfs(1,n,0);
    dfs(1,n,1);
    ll u=0;
    for(ll i=1; i<=n; i++){
        if(!vis[i][0]) u++;
        if(!vis[i][1]) u++;
    }
    return (u==0)? true : false;
}

int main()
{
    ll n, m; cin>> n>> m;
    for(ll i=0; i<=n; i++){
        for(ll j=0; j<=n; j++){
            adj[i][j][0]=false;
            adj[i][j][1]=false;
        }
    }
    ll g, h;
    ll w;
    priority_queue< pair< ll, pll > > pq;
    for(ll i=0; i<m; i++){
        cin>> g>> h>> w;
        if(w==1 || w==3){
            adj[g][h][0]=true;
            adj[h][g][0]=true;
        }
        if(w==2 || w==3){
            adj[g][h][1]=true;
            adj[h][g][1]=true;
        }
        pq.push(mp(3-w,mp(g,h)));
    }
    while(!pq.empty()){
        pair< double, pll > s = pq.top();
        pq.pop();
        g=s.y.x;
        h=s.y.y;
        w=s.x;
        w=3-w;
        if(w==1 || w==3){
            adj[g][h][0]=false;
            adj[h][g][0]=false;
        }
        if(w==2 || w==3){
            adj[g][h][1]=false;
            adj[h][g][1]=false;
        }
        if(!isConnected(n)){
            if(w==1 || w==3){
                adj[g][h][0]=true;
                adj[h][g][0]=true;
            }
            if(w==2 || w==3){
                adj[g][h][1]=true;
                adj[h][g][1]=true;
            }
            m--;
        }
    }
    cout<< m<< endl;
}
/*
5 7
1 2 3
2 3 3
3 4 3
5 3 2
5 4 1
5 2 2
1 5 1
*/


