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


    bool isConnected(){
        clearVis();
        dfs(si);
        ll w=0;
        for(ll i=si; i<=ei; i++){
            if(!vis[i]) w++;
        }
        return (w==0)? true : false;
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

    ll countComponent(){
        ll r=0;
        clearVis();
        for(ll i=si; i<=ei; i++){
            if(!vis[i]){
                r++;
                dfs(i);
            }
        }
        return r;
    }

	void dfsForPrintSCC(int v, stack<int> &Stack)
    {
        vis[v] = true;
        for(int i=0; i < adj[v].size(); i++)
            if(!vis[adj[v][i].x])
                dfsForPrintSCC(adj[v][i].x, Stack);
        Stack.push(v);
    }

	void printSCCs()
    {
        stack<int> Stack;
        this->clearVis();

        for(int i = si; i <=ei; i++){
            if(vis[i] == false) dfsForPrintSCC(i, Stack);
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


    void dfsForSCC(int v, vector<ll>* ccs, bool show=false)
    {
        vis[v] = true;
        if(show) cout << v << " ";
        ccs->push_back(v);
        //insert function or implementation on node :3
        for (int i=0; i < adj[v].size(); i++){
            if (!vis[adj[v][i].x]){
                dfsForSCC(adj[v][i].x,ccs,show);
        //insert function or implementation on children :3
            }
        }
    }

    vector< vector<ll> > SCC()
    {
        stack<int> Stack;
        this->clearVis();

        for(int i = si; i <=ei; i++){
            if(vis[i] == false) dfsForPrintSCC(i, Stack);
        }

        Graph gr = getTranspose();

        gr.clearVis();
        vector< vector<ll> > ans;
        while (Stack.empty() == false){
            int v = Stack.top();
            Stack.pop();
            if (gr.vis[v] == false){
                vector<ll> ccs;
                gr.dfsForSCC(v,&ccs,false);
                ans.push_back(ccs);
            }
        }
        return ans;
    }

	Graph getTranspose()
    {
        Graph g(V);
        for (int v = si; v <= ei; v++)
        {
            for(int i = 0; i< adj[v].size(); i++)
            {
                g.addEdge(adj[v][i].x,v, false);
            }
        }
        return g;
    }

    ll kpar(ll n, ll* dsup){
        if(dsup[n]==n) return n;
        return kpar(dsup[n],dsup);
    }

    void kcon(ll u, ll v, ll* dsup, ll* dsus){
        if(dsus[u]<dsus[v]) swap(u,v);
        dsus[u]+=dsus[v];
        dsus[v]=0;
        dsup[v]=u;
        return;
    }

    Graph mstKruskal(bool show=true){
        Graph gr(V,false,this->one);
        ll* dsuS;
        ll* dsuP;
        dsuP = new ll[V+1];
        dsuS = new ll[V+1];
        for(ll i=si; i<=ei; i++){
            dsuS[i]=1;  dsuP[i]=i;
        }
        vector< pair< double, pll > > edge;
        for(ll i=si; i<=ei; i++){
            for(ll j=0; j<adj[i].size(); j++){
                edge.push_back( mp(adj[i][j].y, mp(adj[i][j].x, i)));
            }
        }
        sort(edge.begin(),edge.end());
        pair< double, pll > mst[V];
        ll r = 0, ans=0;
        for(ll i=0; i<edge.size() && r<V-1; i++){
            ll g = kpar(edge[i].y.x,dsuP);
            ll h = kpar(edge[i].y.y,dsuP);
            if(g!=h){
                mst[r]=edge[i]; r++;
                ans+=edge[i].x;
                kcon(g,h,dsuP,dsuS);
            }
        }
        for(ll i=0; i<r; i++){
            if(show) cout<< mst[i].y.x<< "_"<< mst[i].y.y<< " w="<< mst[i].x<< "\n";
            gr.addEdge(mst[i].y.x, mst[i].y.y, true, mst[i].x);
        }
        return gr;
    }

    Graph mstPrim(bool show = false){
        ll from=si;
        Graph g0(V,false,this->one);
        clearVis();
        double* distance= new double[V+1];
        for(ll i=0; i<=V; i++) distance[i]=100000000;
        distance[from]=0;
        priority_queue< pair< pdl, pld > > q;
        q.push(mp(mp(0,from),mp(-1,0)));
        while(!q.empty()){
            ll a=q.top().x.y, p=q.top().y.x;
            double z=q.top().y.y;
            q.pop();
            if(vis[a]) continue;
            vis[a]=true;
            if(p!=-1) g0.addEdge(p,a,true,z);
            for(ll i=0; i<adj[a].size(); i++){
                ll b=adj[a][i].x;
                double w=adj[a][i].y;
                if(w < distance[b]){
                    distance[b] = w;
                    q.push(mp(mp(-distance[b],b),mp(a,w)));
                }
            }
        }
        return g0;
    }

    void dfsForTsort(int v, stack<ll>& s)
    {
        vis[v] = true;
        for (int i=0; i < adj[v].size(); i++){
            if (!vis[adj[v][i].x]){
                dfsForTsort(adj[v][i].x,s);
            }
        }
        s.push(v);
        return;
    }

    ll* topologicalSort(){
        stack<ll> s;
        clearVis();
        for(int i=si; i<=ei; i++){
            if(!vis[i]){
                dfsForTsort(i,s);
            }
        }
        ll* ans= new ll(V);
        for(ll i=0; i<V; i++){
            ans[i]=s.top();
            s.pop();
        }
        return ans;
    }

    void dijkstra(ll from, ll to){
        clearVis();
        double* distance= new double[V+1];
        ll* par = new ll[V+1];
        for(ll i=0; i<=V; i++) distance[i]=1000000000;
        distance[from]=0;
        priority_queue< pdl > q;
        par[from]=-1;
        q.push(mp(0,from));
        while(!q.empty()){
            ll a=q.top().y;
            q.pop();
            if(vis[a]) continue;
            vis[a]=true;
            for(ll i=0; i<adj[a].size(); i++){
                ll b=adj[a][i].x;
                double w=adj[a][i].y;
                if(distance[a]+w < distance[b]){
                    par[b]=a;
                    distance[b] = distance[a]+w;
                    q.push(mp(-distance[b],b));
                }
            }
        }


        cout<< "Shortest path cost: "<< distance[to]<< endl;
        vector<ll> path;
        if(distance[to]<100000000){
            ll n=to;
            while(n!=-1){
                path.push_back(n);
                n=par[n];
            }
        }
        for(ll i=path.size()-1; i>=0; i--){
            cout<< path[i];
            if(i!=0) cout<< "->";
        }
        cout<< endl;
        return;
    }

    void bellmanford(ll from, ll to){
        double* distance;
        ll* par;
        distance = new double[V+1];
        par = new ll[V+1];
        for(ll i=0; i<=V; i++) distance[i]=1000000000;
        distance[from]=0;
        par[from]=-1;
        for(ll j=0; j<V-1; j++){
            for(ll i=si; i<=ei; i++){
                for(ll k=0; k<adj[i].size(); k++){
                    ll b=adj[i][k].x;
                    double w=adj[i][k].y;
                    if(distance[b]>distance[i]+w) par[b]=i;
                    distance[b]=min(distance[b],distance[i]+w);
                }
            }
        }

        for(ll i=si; i<=ei; i++){
            for(ll k=0; k<adj[i].size(); k++){
                ll b=adj[i][k].x;
                double w=adj[i][k].y;
                if(distance[b]>distance[i]+w){
                    cout<< "The graph contains a negative cycle\n";
                    return;
                }
            }
        }


        cout<< "The graph does not contain a negative cycle\nShortest path cost: "<< distance[to]<< endl;
        vector<ll> path;
        if(distance[to]<100000000){
            ll n=to;
            while(n!=-1){
                path.push_back(n);
                n=par[n];
            }
        }
        for(ll i=path.size()-1; i>=0; i--){
            cout<< path[i];
            if(i!=0) cout<< "->";
        }
        cout<< endl;
        return;
    }


    ll* bipartite(){
        ll* color= new ll[V+1];
        for(ll i=0; i<=V; i++) color[i]=0;
        ll w=0;
        for(ll i=si; i<=ei; i++){
            if(!vis[i]){
                queue<ll> q;
                q.push(i);
                color[i]=1
                vis[i]=true;
                while(!q.empty()){
                    int k = q.front();
                    q.pop();
                    if(show) cout << k << " ";
                    //insert function or implementation on node :3
                    for (int i=0; i < adj[k].size(); i++){
                        if (!vis[adj[k][i].x]){
                            q.push(adj[k][i].x);
                            color[adj[k][i].x]=3-color[k];
                            vis[adj[k][i].x]=true;
                        }
                    }
                }
            }
        }
        for(ll i=si; i<=ei; i++){
            for(ll j=0; j<adj[i].size(); j++){
                ll k=adj[i][j].x;
                if(color[i]+color[k]!=3) w++;
            }
        }
        if(w!=0){
            for(ll i=0; i<=V; i++) color[i]=0;
        }
        return color;
    }

    db** makeMat(){
        db** mat = new db*[V+1];
        for(ll i=0; i<=V; i++){
            mat[i]=new db[V+1];
            for(ll j=0; j<=V; j++){
                mat[i][j]=1000000000;
            }
            mat[i][i]=0;
        }
        for(ll i=si; i<=ei; i++){
            for(ll j=0; j<adj[i].size(); j++){
                ll k=adj[i][j].x;
                mat[i][k]=adj[i][j].y;
            }
        }
        return mat;
    }

    db** shorten(db** L1, db** L2){
        db** M = new db*[V+1];
        for(ll i=0; i<=V; i++)  M[i]=new db[V+1];

        for(ll i=si; i<=ei; i++){
            for(ll j=si; j<=ei; j++){
                M[i][j]=1000000000;
                for(ll k=si; k<=ei; k++){
                    M[i][j]=min(M[i][j],L1[i][k]+L2[k][j]);
                }
            }
        }

        return M;
    }

    db** matExpo(ll n, db** L){
        db** M = new db*[V+1];
        for(ll i=0; i<=V; i++){
            M[i]=new db[V+1];
            for(ll j=0; j<=V; j++){
                M[i][j]=1000000000;
            }
            M[i][i]=0;
        }

        if(n==0)return M;

        M=matExpo(n/2,L);
        M=shorten(M,M);
        if(n%2==1) M=shorten(M,L);
        return M;
    }

    db** apspMatrix(ll n = -1){
        if(n==-1) n=V-1;
        db** mat = this->makeMat();
        return matExpo(n,mat);
    }

    db** apspFWarshall(ll n = -1){
        if(n==-1) n=V;
        db** M1 = this->makeMat();
        db** M2 = this->makeMat();
        for(ll k=si; k<=ei; k++){
            for(ll i=si; i<=ei; i++){
                for(ll j=si; j<=ei; j++){
                    M2[i][j]=min(M1[i][j],M1[i][k]+M1[k][i]);
                }
            }
            for(ll i=si; i<=ei; i++){
                for(ll j=si; j<=ei; j++){
                    M1[i][j]=M2[i][j];
                }
            }
        }
        return M1;
    }
};
