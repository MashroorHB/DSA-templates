# DSA-templates
#Graph.h:
	variables:
      		V: no. of vertices
      		E: no. of edges
      		dir: is Directed or not
      		adj: adjacency vector for edges
      		vis: is Visited array
		one: one initiated or not
		si: starting vertex
		ei: ending vertex
  	functions:
     	 	Graph(int,bool): initiate with number of vertices, zero edges
      		dfs(int,bool): lol
      		bfs(int,bool): lol
		addEdge(int,int,bool,int): create edge from g to h, with weight w
      		clearVis: lol
		isConnected: one single component or not
		totalWeight: lol
		showEdges: lol
		countComponent: lol
     		printSCCs: lol
			dfsForPrintSCC: custom dfs for printSCC idk I copied this from gfg
     		SCC: lol
			dfsForSCC: custom dfs for SCC idk I copied this from gfg
      		getTranspose: generate graph with all edges inverted
      		mstKruskal: generate mst subgraph using kruskal's algo
		mstPrim: generate mst subgraph using kruskal's algo
		topologicalSort: generate an array with nodes of a DAG sorted topologically
			dfsForTsort: custom dfs for topSort idk I did not copy this from gfg
		dijkstra: print shortest path cost using djikstra
		bellmanford: lol
		bipartite: assign colors if bipartite
		
