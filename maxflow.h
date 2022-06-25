#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define mp make_pair

class Graph
{
public:
	int V;
	int E;
	int** adj;
	bool *vis;

    Graph(int n);
    void addEdge(int g, int h, int w=1);
    void clearVis();
    bool bfs(int** rGraph, int s, int t, int* parent);
    bool bfs(int** rGraph, int s);
    int fordFulkerson(int s, int t);
    void mincut(int** rGraph, int s);
};

Graph::Graph(int n)
    {
        this->V = n;
        this->E=0;
        adj = new int*[V+1];
        for(int i=0; i<=V; i++){
            adj[i]=new int[V+1];
            for(int j=0; j<=V; j++) adj[i][j]=0;
        }
        vis = new bool[V+1];
    }

void Graph::addEdge(int g, int h, int w)
    {
        adj[g][h]=w;
        E++;
    }

void Graph::clearVis(){
        for(int i=0; i<=V; i++){
            vis[i]=false;
        }
	};

bool Graph::bfs(int** rGraph, int s, int t, int* parent)
    {
        clearVis();
        queue<int> q;
        q.push(s);
        vis[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v <= V; v++) {
                if (vis[v] == false && rGraph[u][v] > 0) {
                    if (v == t) {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    vis[v] = true;
                }
            }
        }

        return false;
    }

bool Graph::bfs(int** rGraph, int s)
    {
        clearVis();
        queue<int> q;
        q.push(s);
        vis[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v <= V; v++) {
                if (vis[v] == false && rGraph[u][v] > 0) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }

        return false;
    }

int Graph::fordFulkerson(int s, int t)
    {
        int u, v;

        int** rGraph= new int*[V+1];
        for(int i=0; i<=V; i++){
            rGraph[i]=new int[V+1];
        }
        for (u = 0; u <= V; u++){
            for (v = 0; v <= V; v++){
                rGraph[u][v] = this->adj[u][v];
            }
        }
        int* parent=new int[V+1];
        int max_flow = 0;
        while (bfs(rGraph, s, t, parent)) {
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }

            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }

            max_flow += path_flow;
        }
        return max_flow;
    }

void Graph::mincut(int** rGraph, int s)
    {
        bfs(rGraph,s);
        vector< pair< pair<int,int>, int > > cut;
        for(int i=0; i<=V; i++){
            for(int j=0; j<=V; j++){
                if(vis[i] && !vis[j] && adj[i][j]>0){
                    cut.push_back(mp(mp(i,j),adj[i][j]));
                    cout<< i<< " . "<< j<< " . "<< adj[i][j]<< endl;
                }
            }
        }
    }
