#pragma once
#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
typedef int ll;

#define pll pair<ll,ll>
#define pld pair<ll,double>
#define pdl pair<double,ll>
#define mp make_pair
#define x first
#define y second

class Graph
{
public:
	int V;
	int E;
	bool dir;
	vector< pld > *adj;
	bool *vis;
	bool *exist;
	bool one;
    int si;
    int ei;

	Graph(int V, bool dir = true, int one=true)
    {
        this->V = V;
        E=0;
        adj = new vector< pld >[V+1];
        vis = new bool[V+1];
        exist = new bool[V+1];
        this->dir = dir;
        this->one = one;
        if(one){
            si=1;
            ei=V;
        }
        else{
            si=0;
            ei=V-1;
        }
    }

    void dfs(int v, bool show=false)
    {
        vis[v] = true;
        if(show) cout << v << " ";
        //insert function or implementation on node :3
        for (int i=0; i < adj[v].size(); i++){
            if (!vis[adj[v][i].x]){
                dfs(adj[v][i].x,show);
        //insert function or implementation on children :3
            }
        }
    }

    void bfs(int n, bool show=false){
        queue<ll> q;
        q.push(n);
        vis[n]=true;
        while(!q.empty()){
            int k = q.front();
            q.pop();
            if(show) cout << k << " ";
            //insert function or implementation on node :3
            for (int i=0; i < adj[k].size(); i++){
                if (!vis[adj[k][i].x]){
                    q.push(adj[k][i].x);
                    vis[adj[k][i].x]=true;
                }
            }
        }
        return;
    }

	void addEdge(int g, int h, bool undir=true, double w=1.0)
    {
        adj[g].push_back(mp(h,w));
        if(undir) adj[h].push_back(mp(g,w));
        E++;
    }

	void clearVis(){
        for(int i=0; i<=V; i++){
            vis[i]=false;
        }
	};

    Graph mstKruskal(bool show = false){
        Graph gr(V,false,this->one);
        pair< double, pll > mst[V];
        ll dsuS[V+1], dsuP[V+1];
        vector<ll> slave[V+1];
        vector< pair< double, pll > > edge;
        for(ll i=si; i<=ei; i++){
            for(ll j=0; j<adj[i].size(); j++){
                edge.push_back( mp(adj[i][j].y, mp(adj[i][j].x, i)));
            }
        }
        sort(edge.begin(),edge.end());
        for(ll i=si; i<=ei; i++){
            dsuS[i]=1;
            dsuP[i]=i;
            slave[i].push_back(i);
        }
        ll r = 0, ans=0;
        for(ll i=0; i<edge.size() && r<V-1; i++){
            ll g = edge[i].y.x;
            ll h = edge[i].y.y;
            if(dsuP[g]!=dsuP[h]){
                mst[r]=edge[i]; r++;
                ans+=edge[i].x;
                g = dsuP[g];
                h = dsuP[h];
                if(dsuS[g]<dsuS[h]) swap(g,h);
                for(ll i=0; i<dsuS[h]; i++){
                    dsuP[slave[h][i]]=g;
                    slave[g].push_back(slave[h][i]);
                }
                dsuS[g]+=dsuS[h];
                dsuS[h]=0;
                slave[h].clear();
            }
        }
        for(ll i=0; i<r; i++){
            if(show) cout<< mst[i].y.x<< "_"<< mst[i].y.y<< " w="<< mst[i].x<< "\n";
            gr.addEdge(mst[i].y.x, mst[i].y.y, true, mst[i].x);
        }
        return gr;

    }

    Graph mstPrim(bool show = false){
        ll g, h, w;
        for(ll i=si; i<=ei; i++){
            for(ll j=0; j<adj[i].size(); j++){
                adj[i][j].y=1000000-adj[i][j].y;
            }
        }
        clearVis();
        priority_queue< pair< pdl , ll> > q;
        queue< pair< pdl , ll> > mst;
        vis[si]=true;
        for(ll i=0; i<adj[si].size(); i++){
            q.push(mp(mp(adj[si][i].y,adj[si][i].x),si));
        }
        while(!q.empty()){
            pair< pdl , ll> s=q.top();
            q.pop();
            if(vis[s.x.y] && vis[s.y]){
                continue;
            }
            else{
                mst.push(s);
                ll vc, pc;
                (vis[s.x.y])? pc=s.x.y : pc=s.y;
                (vis[s.x.y])? vc=s.y : vc=s.x.y;
                //cin>> vc;
                ll kw=s.x.x;
                //cin>> kw;
                kw=1000000-kw;
                vis[vc]=true;
                for(ll i=0; i<adj[vc].size(); i++){
                    if(!vis[adj[vc][i].x]){
                        q.push(mp(mp(adj[vc][i].y,adj[vc][i].x),vc));
                    }
                }
            }
        }
        Graph gr(V,false,this->one);
        while(!mst.empty()){
            pair< pdl , ll> s=mst.front();
            mst.pop();
                s.x.x=1000000-s.x.x;
            if(show) cout<< s.x.y<< "_"<< s.y<< " w="<< s.x.x<< "\n";
            gr.addEdge(s.x.y, s.y, true, s.x.x);
        }
        return gr;
    }

    double totalWeight(){
        double sum=0;
        for(ll i=si; i<=ei; i++){
            for(ll j=0; j<adj[i].size(); j++){
                ll k=adj[i][j].x;
                if(k>i || this->dir) sum+=adj[i][j].y;
            }
        }
        return sum;
    }

    void showEdges(){
        cout<< "{";
        ll r=this->E;
        for(ll i=si; i<=ei; i++){
            for(ll j=0; j<adj[i].size(); j++){
                ll k=adj[i][j].x;
                if(k>i || this->dir){
                    cout<< "("<< i<< ","<< k<< ")";
                    r--;
                    if(r>0) cout<< ",";
                }
            }
        }
        cout<< "}\n";
    }
};
