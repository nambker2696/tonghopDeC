#ifndef	_GRAPH_H_
#define	_GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "../libfdr/jrb.h"
#include "../libfdr/dllist.h"
#include "util.h"

#ifndef INFINITY_
#define INFINITY_	100000
#endif

#ifndef MAXVERTICE
#define MAXVERTICE	1000
#endif

#ifndef BUFF_SIZE
#define BUFF_SIZE	80
#endif

#ifndef ARRSIZE
#define ARRSIZE	1000
#endif

typedef struct 
{
	JRB vertices;
	JRB edges;
} Graph;

/* Init and Destroy */
Graph 	CreateGraph(void);
void 	DropGraph(Graph G);

/* Create Vertice and Edge */
void 	AddVertice(Graph G, int id, char *name);
void 	AddEdge(Graph G, int v1, int v2, double weight, int indirected); //indirected==true: indirected edge.

/* Vertice's relationship */
int 	IsAdjacent(Graph G, int v1, int v2);
int 	Indegree(Graph G, int v, int* output);
int 	Outdegree(Graph G, int v, int* output);
double 	GetEdgeValue(Graph G, int u, int v);
char*	GetVerticeName(Graph G, int v);

/* Traversal (Set stop = -1 if you want to traverse all vertices) */
void 	BFS(Graph G, int start, int stop);
void 	DFS(Graph G, int start, int stop);

/* Advanced functions*/
int 	IsDAG(Graph G);
void 	TopologicalSort(Graph G);
void	ShortestPath(Graph G, int start, int end, int* path, int* sizeofPath, double *totalLength);

/* */
void 	ShowAdjacentVerticle(Graph G, int v);
int 	Visit(Graph G, int v);

/**********************************************************/
/*                         graph.c                        */
/**********************************************************/
//---------------------------------------------------------
Graph CreateGraph(void)
{
	Graph G;
	G.vertices = make_jrb();
	G.edges = make_jrb();
	if (G.vertices == NULL || G.edges == NULL)
	{
		printf("%s\n", "Could not create graph! ERROR: make_jrb failed!");
	}
	return G;
}
//---------------------------------------------------------
void DropGraph(Graph G)
{	
	JRB node;
	
	jrb_free_tree(G.vertices);

	jrb_traverse(node, G.edges)
		jrb_free_tree( jval_v(node->val) );
}
//---------------------------------------------------------
void AddVertice(Graph G, int id, char *name)
{
	JRB node = make_jrb();
	node = jrb_find_int(G.vertices, id);

	if (node == NULL)
	{
		jrb_insert_int(G.vertices, id, new_jval_s(strdup(name))); // insert new
	}
	else
	{
		strcpy(jval_s(node->val), name); // update
	}
}
//---------------------------------------------------------
void AddEdge(Graph G, int v1, int v2, double weight, int indirected)
{
	if (v1 == v2) return; //A vertex doesnt have path to itself

	JRB tree = make_jrb();
	JRB node = make_jrb();
	node = jrb_find_int(G.edges, v1);
	
	if (node == NULL)
	{
		jrb_insert_int(G.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_d(weight));
	}
	else
	{
		tree = (JRB)jval_v(node->val);
		if (jrb_find_int(tree, v2) == NULL)
		{
			jrb_insert_int(tree, v2, new_jval_d(weight));
		}
	}

	if (indirected)
		AddEdge(G, v2, v1, weight, 0);
}
//---------------------------------------------------------
int IsAdjacent(Graph G, int v1, int v2)
{
	JRB node = jrb_find_int(G.edges, v1);
	if (node == NULL) 
		return 0;
	else
	{
		JRB adjacentTree = make_jrb();
		adjacentTree = (JRB)jval_v(node->val);
		JRB temp = jrb_find_int(adjacentTree, v2);
		if (temp != NULL)
			return 1;
	}
	return 0;
}
//---------------------------------------------------------
int Indegree(Graph G, int v, int* output)
{
	JRB findv;
	findv = jrb_find_int(G.vertices, v);
	int total = 0;

	if (findv == NULL)
	{
		//printf("%s\n", "Vertex does not exist!");
		return -1;
	}

	JRB p;// = make_jrb();
	JRB node;// = make_jrb();

	jrb_traverse(node, G.edges)
	{
		JRB tree = (JRB)jval_v(node->val);
		jrb_traverse(p, tree)
		{
			if (jval_i(p->key) == v)
			{
				if (output == NULL) total++;
				else output[total++] = jval_i(node->key);
			}
		}
	}

	return total;
}
//---------------------------------------------------------
int Outdegree(Graph G, int v, int* output)
{
	JRB node;
	node = jrb_find_int(G.edges, v);

	if (node == NULL)
	{
		//printf("%s\n", "Vertex does not exist!");
		return -1;
	}

	JRB tree = (JRB)jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree)
		output[total++] = jval_i(node->key);

	return total;
}
//---------------------------------------------------------
double GetEdgeValue(Graph G, int u, int v)
{
	JRB node = jrb_find_int(G.edges, u);
	if (NULL == node)
		return INFINITY_;
	
	JRB adjacentTree = make_jrb();
	adjacentTree = (JRB)jval_v(node->val);
	node = jrb_find_int(adjacentTree, v);
	if (NULL == node)
		return INFINITY_;
	else
		return jval_d(node->val);
}
char* GetVerticeName(Graph G, int v)
{
	char* name = (char*)malloc(BUFF_SIZE*sizeof(char));
	strcpy(name, "NULL");
	JRB find = jrb_find_int(G.vertices, v);
	if (find == NULL)
	{
		printf("Vertex does not exists!\n");
		return name;
	}
	else

	strcpy(name, jval_s(find->val));
	return name;
}
//---------------------------------------------------------
void BFS(Graph G, int start, int stop)
{
	Dllist l = new_dllist();
	Dllist visited = new_dllist();

	JRB find = jrb_find_int(G.vertices, start);
	if (find == NULL)
	{
		printf("Start vertex is not vaild! Vertex does not exists!\n");
		return;
	}

	dll_append(l, new_jval_i(start));

	while (!dll_empty(l))
	{
		int u = jval_i(dll_first(l)->val);
		dll_delete_node(dll_first(l));

		if (!dll_find(visited, u))
		{
			// Do something with this vertex here!!!!!!!!!!!!!!!!!!!!
			printf("%d ", u);

			if (stop == u)
				return;

			dll_append(visited, new_jval_i(u));
			
			int output[ARRSIZE];
			int n = Outdegree(G, u, output);
			if (n != 0)
			{
				int i;
				for (i = 0; i < n; i++) 
				{
					if (!dll_find(visited, output[i]))
					{
						dll_append(l, new_jval_i(output[i]));
					}
				}
			}
		}
	}

	free_dllist(visited);
}
//---------------------------------------------------------
void DFS(Graph G, int start, int stop)
{
	Dllist l = new_dllist();
	Dllist visited = new_dllist();
	JRB find = jrb_find_int(G.vertices, start);
	if (find == NULL)
	{
		printf("Start vertex is not vaild! Vertex does not exists!\n");
		return;
	}

	dll_append(l, new_jval_i(start));

	while (!dll_empty(l))
	{
		int u = jval_i(dll_last(l)->val);
		dll_delete_node(dll_last(l));

		if (!dll_find(visited, u))
		{
			// Do something with this vertex here!!!!!!!!!!!!!!!!!!!!
			printf("%d ", u);

			if (stop == u)
				return;

			dll_append(visited, new_jval_i(u));
			
			int output[ARRSIZE];
			int n = Outdegree(G, u, output);
			if (n != 0)
			{
				int i;
				for (i = n-1; i >= 0; i--) 
				{
					if (!dll_find(visited, output[i]))
						dll_append(l, new_jval_i(output[i]));
				}
			}
		}
	}

	free_dllist(visited);
}
//---------------------------------------------------------
int IsDAG(Graph G)
{
	Dllist arbitraryVertice = new_dllist();

	JRB node;
	jrb_traverse(node, G.vertices)
	{
		dll_append(arbitraryVertice, (node->key));
	}

	while (!dll_empty(arbitraryVertice))
	{
		Dllist l = new_dllist();
		int source = jval_i(dll_first(arbitraryVertice)->val);
		dll_append(l, new_jval_i(source));
		dll_delete_node(dll_first(arbitraryVertice));
		
		Dllist visited = new_dllist();
		while (!dll_empty(l))
		{
			int u = jval_i(dll_last(l)->val);
			dll_delete_node(dll_last(l));

			if (!dll_find(visited, u))
			{
				dll_append(visited, new_jval_i(u));
				
				int output[ARRSIZE];
				int n = Outdegree(G, u, output);
				if (n != 0)
				{
					int i;
					for (i = n-1; i >= 0; i--) 
					{
						if (!dll_find(visited, output[i]))
						{
							dll_append(l, new_jval_i(output[i]));
						}
						else if (output[i] == source)
						{
							free_dllist(visited);
							free_dllist(l);
							free_dllist(arbitraryVertice);
							return 1;
						}
					}
				}
			}
		}
	}

	free_dllist(arbitraryVertice);
	return 0;
}
//---------------------------------------------------------
void TopologicalSort(Graph G)
{
	if (IsDAG(G))
	{
		printf("Can not make topological sort\n"); 
		return; 
	}

	Dllist tpQueue = new_dllist();
	JRB indegree = make_jrb();
	JRB node;

	jrb_traverse(node, G.vertices)
	{
		int iv = Indegree(G, jval_i(node->key), NULL);
		jrb_insert_int(indegree, jval_i(node->key), new_jval_i(iv));
		if (iv == 0)
			dll_append(tpQueue, node->key);
	}
	
	while (!dll_empty(tpQueue))
	{
		Visit(G, jval_i(dll_first(tpQueue)->val));

		int arc[ARRSIZE]; 
		int sizeofArc = Outdegree(G, jval_i(dll_first(tpQueue)->val), arc);

		dll_delete_node(dll_first(tpQueue));
		
		int i;
		for(i = 0; i < sizeofArc; i++)
		{
			JRB tmp;
			tmp = jrb_find_int(indegree, arc[i]);

			if (tmp != NULL)
			{
				tmp->val = new_jval_i(jval_i(tmp->val)-1);
				if (jval_i(tmp->val) <= 0)
					dll_append(tpQueue, tmp->key);
			}	
		}
	}

	jrb_free_tree(indegree);
}
//---------------------------------------------------------
void ShortestPath(Graph G, int start, int end, int* path, int* sizeofPath, double *totalLength)
{
	// This funcion base on Dijkstra Algorithm
	double distance[MAXVERTICE];
	double min;
	int previous[MAXVERTICE];
	
	// Initial
	int i;
	int u;
	for (i = 0; i < MAXVERTICE; ++i)
		distance[i] = INFINITY_;

	// Set first start to priority queue
	previous[start] = start;
	distance[start] = 0.00000;
	Dllist pQueue = new_dllist();
	Dllist visited = new_dllist();
	dll_append(pQueue, new_jval_i(start));

	Dllist dequeue;

	while (!dll_empty(pQueue))
	{
		// Extract min
		min = INFINITY_;
		Dllist ptr;
		dll_traverse(ptr, pQueue)
		{
			u = jval_i(ptr->val);
			if (CompareDouble(min, distance[u]) > 0)
			//if (min > distance[u])
			{
				min = distance[u];
				dequeue = ptr;
			}
		}
		u = jval_i(dequeue->val);
		dll_delete_node(dequeue);

		if (u == end)
			break;

		// Relax
		int output[100];
		int numnberofAdjacentVertice = Outdegree(G, u, output);
		for (i = 0; i < numnberofAdjacentVertice; ++i)
		{
			int v = output[i];
			double w = GetEdgeValue(G, u, v);

			if (CompareDouble(distance[v], distance[u] + w) > 0)
			//if (distance[v] > distance[u] + w)
			{
				distance[v] = distance[u] + w;
				previous[v] = u;
			}
			
			// Modify key
			int foundInQueue = 0;
			dll_traverse(ptr, visited)
			{
				int t = jval_i(ptr->val);
				if (v == t)
					foundInQueue = 1;
			}
			if (foundInQueue != 1)
			{
				dll_append(pQueue, new_jval_i(v));
				dll_append(visited, new_jval_i(v));
			}
		}
	}

	*sizeofPath = 0;
	*totalLength = distance[end];

	if (distance[end] != INFINITY_)
	{
		while (end != start)
		{
			path[(*sizeofPath)++] = end;
			end = previous[end];
		}
		path[(*sizeofPath)++] = start;	
	}
}

//--------------------------------------------------------
void ShowAdjacentVerticle(Graph G, int v)
{
	int output[ARRSIZE];
	int n = Outdegree(G, v, output);

	if (n == 0) 
		printf("No adjacent vertices\n");
	else 
	{
		printf("%s %d: \n", "Vertice", v);
		printf("Number of adjacent: %d\n", n);
		printf("Adjacent vertices:");
		int i;
		for (i=0; i< n; i++) 
			printf("%5d", output[i]);
	}
	printf("%s\n", "");
}
//---------------------------------------------------------
int Visit(Graph G, int v)
{
	JRB node;
	node = jrb_find_int(G.vertices, v);
	printf("%s ", jval_s(node->val));
	return 0;
}

#endif