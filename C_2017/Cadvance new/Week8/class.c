#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <string.h>

typedef struct class_s {
     char name[100];
} class;

typedef struct map_s {
     class *class_list;
     int class_num;
     graph graph;
} map;

int output[100];
map data;

map get_data_from_file(const char *file_name);
void print_node(graph, int);

int main(int argc, char const *argv[]){
     //int i, n ,output[100];
     if (argc != 2) {
          printf("%s\n./%s %s", "WRONG FORMAT !!\n", argv[0],
                 ".graph file"
                );
          exit(1);
     }

     data.graph = create_graph();

     //char givenName[100];
     data = get_data_from_file(argv[1]);

     // int i;
     // for (i = 0; i < data.class_num; i++)
     // {
     //      printf("%s\n",data.class_list[i].name);
     // }

     // printf("%s", get_vertex(data.graph, 3));
     // printf("%d\n", in_degree(data.graph, 4, output));


     if (is_cyclic(data.graph)) { 
          printf("Cannot make topological sort\n");
          return 1; 
     }
    
     printf("%s\n", "Check TSort");
     TSort(data.graph, print_node);
     printf("\n");
     // printf("%s\n", "Check cycle");
     // if(is_cyclic(g)){
     //      printf("%s\n", "graph has cycle");
     // } else {
     //      printf("%s\n", "graph has no cycle");
     // }
     
     printf("\n\nTest drop !\n");
     
     free(data.class_list);               //cuz we use malloc
     drop_graph(&(data.graph));
     
     return 0;
}

int findClass(char* className, map g){
     int i;
     for (i = 0; i < g.class_num; i++)
     {
          if (strcmp(g.class_list[i].name, className) == 0)
          {
               return 0;
          }
     }
     return 1;
}

int findIndex(char* className, map g){
     int i;
     for (i = 0; i < g.class_num; i++)
     {
          if (strcmp(g.class_list[i].name, className) == 0)
          {
               return i;
          }
     }
     return 0;
}


void print_node(graph g, int i){
     printf("\t%s", data.class_list[i].name);
}

map get_data_from_file(const char * filename){
     FILE *f = fopen(filename, "r");
     if (f == NULL) {
        fprintf(stderr, "Can't Open file %s !!\n", filename);
        exit(1);
     }

     int flag = 0;
     int MAX = 20;
     int v1, v2;
     char prefix[100], className[100];
     map ret;
     ret.class_list = (class *)malloc(sizeof(class) * MAX);
     ret.class_num = 0;
     ret.graph = create_graph();

     char temp[100];
     while(1){
          flag = 0;
          //CLASS
          fgets(temp, 100, f);

          if (strcmp(temp, "\n") == 0)
          {
               //blank line so continue to scan
               continue;
          }
          sscanf(temp, "%s %[^\n]", prefix, className);
          if (findClass(className, ret) == 1)
          {
               printf("%s\n", className);

               //new record to add
               if (strcmp(prefix, "CLASS") == 0)
               {
                    v2 = ret.class_num;
               }else if (strcmp(prefix, "PREREQ") == 0)
               {
                    flag = 1;
                    v1 = ret.class_num;
               }
               add_vertex(ret.graph, ret.class_num, className);
               strcpy(ret.class_list[ret.class_num].name, className);
               ret.class_num ++;
          }else{
               //table already has that record
               if (strcmp(prefix, "CLASS") == 0)
               {
                    v2 = findIndex(className, ret);
               }else if (strcmp(prefix, "PREREQ") == 0)
               {
                    flag = 1;
                    v1 = findIndex(className, ret);
               }
          }
          if (flag == 1)
          {
               add_edge(ret.graph, v1, v2);
               
          }
          if (feof(f))
          {
               break;
          }
     }
     fclose(f);
     return ret;
}