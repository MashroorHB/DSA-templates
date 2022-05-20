# DSA-templates
#Graph.h:
  variables:
      V: no. of vertices
      E: no. of edges
      dir: is Directed or not
      adj: adjacency vector for edges
      vis: is Visited array
  functions:
      Graph(int,bool): initiate with number of vertices, zero edges
      dfs(int,bool): lol
      bfs(int,bool): lol
      addEdge(int,int,bool,int): create edge from g to h, with weight w
      clearVis: lol
      printSCCs: lol
      getTranspose: generate graph with all edges inverted
      mstKruskal: generate mst subgraph using kruskal's algo
