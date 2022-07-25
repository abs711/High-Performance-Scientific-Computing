from scipy.io import mmread
import networkx as nx
import sys
import time

def pagerank(G, alpha=0.85, personalization=None, 
			max_iter=100, tol=1.0e-6, nstart=None, weight='weight', 
			dangling=None): 
	"""Return the PageRank of the nodes in the graph. 

	PageRank computes a ranking of the nodes in the graph G based on 
	the structure of the incoming links. It was originally designed as 
	an algorithm to rank web pages. 

	Parameters 
	---------- 
	G : graph 
	A NetworkX graph. Undirected graphs will be converted to a directed 
	graph with two directed edges for each undirected edge. 

	alpha : float, optional 
	Damping parameter for PageRank, default=0.85. 

	personalization: dict, optional 
	The "personalization vector" consisting of a dictionary with a 
	key for every graph node and nonzero personalization value for each node. 
	By default, a uniform distribution is used. 

	max_iter : integer, optional 
	Maximum number of iterations in power method eigenvalue solver. 

	tol : float, optional 
	Error tolerance used to check convergence in power method solver. 

	nstart : dictionary, optional 
	Starting value of PageRank iteration for each node. 

	weight : key, optional 
	Edge data key to use as weight. If None weights are set to 1. 

	dangling: dict, optional 
	The outedges to be assigned to any "dangling" nodes, i.e., nodes without 
	any outedges. The dict key is the node the outedge points to and the dict 
	value is the weight of that outedge. By default, dangling nodes are given 
	outedges according to the personalization vector (uniform if not 
	specified). This must be selected to result in an irreducible transition 
	matrix (see notes under google_matrix). It may be common to have the 
	dangling dict to be the same as the personalization dict. 

	Returns 
	------- 
	pagerank : dictionary 
	Dictionary of nodes with PageRank as value 

	Notes 
	----- 
	The eigenvector calculation is done by the power iteration method 
	and has no guarantee of convergence. The iteration will stop 
	after max_iter iterations or an error tolerance of 
	number_of_nodes(G)*tol has been reached. 

	The PageRank algorithm was designed for directed graphs but this 
	algorithm does not check if the input graph is directed and will 
	execute on undirected graphs by converting each edge in the 
	directed graph to two edges. 

	
	"""
	if len(G) == 0: 
		return {} 

	if not G.is_directed(): 
		D = G.to_directed() 
	else: 
		D = G 

	# Create a copy in (right) stochastic form 
	W = nx.stochastic_graph(D, weight=weight) 
	N = W.number_of_nodes() 


	# Choose fixed starting vector if not given 
	if nstart is None: 
		x = dict.fromkeys(W, 1.0 / N) 
	else: 
		# Normalized nstart vector 
		s = float(sum(nstart.values())) 
		x = dict((k, v / s) for k, v in nstart.items()) 

	y = dict.fromkeys(x.keys(), 0)

	# power iteration: make up to max_iter iterations 
	for _ in range(max_iter): 
		xlast = x 
		x = dict.fromkeys(xlast.keys(), 0) 
		for n in x: 

			# this matrix multiply looks odd because it is 
			# doing a left multiply x^T=xlast^T*W 
			for nbr in W[n]: 
				x[nbr] += alpha * xlast[n] * W[n][nbr][weight] 
			x[n] += (1.0 - alpha)/N;

		# check convergence, l1 norm 
		err = sum([abs(x[n] - xlast[n]) for n in x]) 
		if err < N*tol: 
			return x 
	raise NetworkXError('pagerank: power iteration failed to converge '
						'in %d iterations.' % max_iter) 




a = mmread(sys.argv[1])

start = time.time()
G = nx.DiGraph(a)
end = time.time()
print("# elapsed time read [read] ", end - start)

start = time.time()
pr = pagerank(G, alpha=0.85)
end = time.time()
print("# elapsed time read [pagerank] ", end - start)

start = time.time()
bb = sorted(pr.items(), key=lambda item: item[1], reverse=True)
end = time.time()
print("# elapsed time read [rank] ", end - start)

for i in range(0,10):
    print(bb[i])
