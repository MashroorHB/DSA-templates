#include<bits/stdc++.h>
#include "graph.h"
using namespace std;
#define test ll t; cin>> t; for(ll u=1; u<=t; u++)


int main(){
        ifstream in("mst.in");
    streambuf *cinbuf = std::cin.rdbuf();
    cin.rdbuf(in.rdbuf());
/*
    ofstream out("out.txt");
    streambuf *coutbuf = std::cout.rdbuf();
    cout.rdbuf(out.rdbuf());
*/
    ll n, m; cin>> n>> m;
    int g, h;
    double w;
    Graph gr(n,false,false);
    for(ll i=0; i<m; i++){
        cin>> g>> h>> w;
        gr.addEdge(g,h,true,w);
    }
    Graph g1 = gr.mstKruskal(false);
    Graph g2 = gr.mstPrim(false);
    cout<< "Cost of the minimum spanning tree : "<< g1.totalWeight()<< endl;
    cout<< "List of edges selected by Prim’s : ";
    g2.showEdges();
    //cout<< g2.totalWeight()<< endl;
    cout<< "List of edges selected by Kruskal’s : ";
    g1.showEdges();
}

/*
7 14
BF 0.2
EG 0.2
CG 0.3
CE 0.4
AD 0.5
AF 0.7
DF 1.3
AB 1.4
EF 1.5
BC 1.5
GF 1.8
BG 1.9
AC 2.1
DE 2.2



*/


