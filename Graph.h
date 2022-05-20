#pragma once
#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
typedef int ll;

#define pll pair<ll,ll>
#define mp make_pair
#define x first
#define y second

class Graph
{
public:
	int V;
	int E;
	bool dir;
	vector< pll > *adj;
	bool *vis;

	void fillOrder(int v, stack<int> &Stack)
    {
        vis[v] = true;
        for(int i=0; i < adj[v].size(); i++)
            if(!vis[adj[v][i].x])
                fillOrder(adj[v][i].x, Stack);
        Stack.push(v);
    }

	Graph(int V, bool dir = true)
    {
        this->V = V;
        E=0;
        adj = new vector< pll >[V+1];
        vis = new bool[V+1];
        this->dir = dir;
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

	void addEdge(int g, int h, bool undir=true, int w=1)
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

	void printSCCs()
    {
        stack<int> Stack;
        this->clearVis();

        for(int i = 1; i <=V; i++){
            if(vis[i] == false) fillOrder(i, Stack);
        }
        Graph gr = getTranspose();

        gr.clearVis();

        while (Stack.empty() == false){
            int v = Stack.top();
            Stack.pop();
            if (gr.vis[v] == false){
                gr.dfs(v,true);
                cout << endl;
            }
        }
    }

	Graph getTranspose()
    {
        Graph g(V);
        for (int v = 1; v <= V; v++)
        {
            for(int i = 0; i< adj[v].size(); i++)
            {
                g.addEdge(adj[v][i].x,v, false);
            }
        }
        return g;
    }

    Graph mstKruskal(bool show = false){
        Graph gr(V);
        pair< ll, pll > mst[V];
        ll dsus[V+1], dsub[V+1];
        vector<ll> slave[V+1];
        vector< pair<ll, pll > > edge;
        for(ll i=1; i<=this->V; i++){
            for(ll j=0; j<adj[i].size(); j++){
                edge.push_back( mp(adj[i][j].y, mp(adj[i][j].x, i)));
            }
        }
        sort(edge.begin(),edge.end());
        for(ll i=1; i<=V; i++){
            dsus[i]=1;
            dsub[i]=i;
            slave[i].push_back(i);
        }
        ll r = 0, ans=0;
        for(ll i=0; i<edge.size() && r<V-1; i++){
            ll g = edge[i].y.x;
            ll h = edge[i].y.y;
            if(dsub[g]!=dsub[h]){
                mst[r]=edge[i]; r++;
                ans+=edge[i].x;
                g = dsub[g];
                h = dsub[h];
                if(dsus[g]<dsus[h]) swap(g,h);
                for(ll i=0; i<dsus[h]; i++){
                    dsub[slave[h][i]]=g;
                    slave[g].push_back(slave[h][i]);
                }
                dsus[g]+=dsus[h];
                dsus[h]=0;
                slave[h].clear();
            }
        }
        for(ll i=0; i<r; i++){
            if(show) cout<< mst[i].y.x<< "_"<< mst[i].y.y<< " w="<< mst[i].x<< "\n";
            gr.addEdge(mst[i].y.x, mst[i].y.y, true, mst[i].x);
        }
        return gr;

    }
};
