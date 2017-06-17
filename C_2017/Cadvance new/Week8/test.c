#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <string.h>

void print_node(graph, int);

int main(int argc, char const *argv[])
{
	graph g = create_graph();
	char ver1[100] = "CS102";
	char ver2[100] = "CS140";
	char ver3[100] = "CS160";
	char ver4[100] = "CS302";
	char ver5[100] = "CS311";
    add_vertex(g, 0, ver1); add_vertex(g, 1, ver2);
    add_vertex(g, 2, ver3); add_vertex(g, 3, ver4);
    add_vertex(g, 4, ver5); add_vertex(g, 5, "MATH300");
    add_edge(g, 0, 1); add_edge(g, 0, 2);
    add_edge(g, 1, 3); add_edge(g, 5, 4); add_edge(g, 3, 4);
    if (is_cyclic(g)) { 
       printf("Cannot make topological sort\n");
       return 1; }
    TSort(g, print_node);
    return 0;
}

void print_node(graph g, int i){
     printf("\t%s", get_vertex(g, i));
}