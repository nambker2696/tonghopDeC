#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct station_s {
     char name[100];
} station;

typedef struct map_s {
     station *stations_list;
     int station_num;
     graph graph;
} map;

map data;

int output[100], n;

map get_data_from_file(const char *file_name);
void PRINT_ADJACENT_VERTIES(int v);
void findAdjacentStations(char* stationName);		

int main(int argc, char const *argv[])
{
	if (argc != 2) {
          printf("%s\n./%s %s", "WRONG FORMAT !!\n", argv[0],
                 ".graph file"
                );
          exit(1);
     }

     data = get_data_from_file(argv[1]);

     int i;
     printf("%s\n", "LIST OF METRO STATIONS");
     for (i = 0; i < data.station_num; i++) {
          printf("%3d. %s\n", i + 1, data.stations_list[i].name);
     }
     printf("\n\n");                   

     PRINT_ADJACENT_VERTIES(1);
     PRINT_ADJACENT_VERTIES(2);
     // PRINT_ADJACENT_VERTIES(3);
     // PRINT_ADJACENT_VERTIES(4);
     // PRINT_ADJACENT_VERTIES(5);
     // PRINT_ADJACENT_VERTIES(9);

     char givenName[100];
     printf("Enter the station name: ");	scanf("%[^\n]s", givenName);
     findAdjacentStations(givenName);

     free(data.stations_list);			//cuz we use malloc
     drop_graph(&(data.graph));
	return 0;
}

void PRINT_ADJACENT_VERTIES(int v){
	n = get_adjacent_vertices(data.graph, v, output);                  
    if(n == 0)                                                
        printf("No adjacent vertices of node %d\n", v);     
    else{                                                     
        printf("Adjacent vertices of node %d: ", v);   
		int i;
        for(i = 0; i < n; i++)                               
            printf("%5d", output[i]);                       
        printf("\n");                                        
	}     
}

void PRINT_ADJACENT_STATIONS(int v){
	n = get_adjacent_vertices(data.graph, v, output);                  
    if(n == 0)                                                
        printf("No adjacent vertices of station %s\n", data.stations_list[v-1].name);     
    else{                                                     
        printf("Adjacent vertices of station %s: ", data.stations_list[v-1].name);   
		int i;
		printf("\n");
        for(i = 0; i < n; i++)                               
            printf("%15s\n", data.stations_list[output[i]-1].name);                       
        printf("\n");                                        
	}     
}

void findAdjacentStations(char *stationName){
	int i;
	for (i = 0; i < data.station_num; i++)
	{
		if (strcmp(data.stations_list[i].name, stationName) == 0)
		{
			PRINT_ADJACENT_STATIONS(i+1);
			break;
		}
	}

}                                                    


map get_data_from_file(const char *file_name){
	FILE *f = fopen(file_name, "r");
     if (f == NULL) {
          fprintf(stderr, "Can't Open file %s !!\n", file_name);
          exit(1);
     }
	char temp[100];	

     //read pass [STATIONS]
     while(1){
     	fgets(temp, 100, f);
     	if (strcmp(temp, "[STATIONS]\n") == 0)
     	{
     		break;
     	}
     }

     //initialize return variable
     int MAX = 10;
     map ret;
     ret.stations_list = (station *)malloc(sizeof(station) * MAX);
     ret.station_num = 0;
     ret.graph = create_graph();

     //station name parse
     while(1){
     	fgets(temp, 100, f);
     	if (strcmp(temp, "[LINES]\n") == 0)
     	{
     		break;
     	}
     	if (strcmp(temp, "\n") == 0)
     	{
     		//blank line so continue to scan
     		continue;
     	}

     	// int i;
      //     for (i = 0; temp[i] != '\0' && temp[i] != '='; i++);
      //     if (temp[i] == '\0')
      //          continue;

     	//realloc if needed
     	if (ret.station_num == MAX -1)
     	{
     		MAX += 10;
     		ret.stations_list = (station *)realloc(ret.stations_list, sizeof(station) * MAX);
     		if (ret.stations_list == NULL) {
                    fprintf(stderr, "Reallocate failed in %s:%d !!\n", __FILE__, __LINE__);
                    exit(1);
               }
     	}

     	sscanf(temp, "S%*d=%[^\n]s\n", ret.stations_list[ret.station_num++].name);
     }

     //lines parse
     while(1){
     	fgets(temp, 100, f);
     	
     	if (strcmp(temp, "\n") == 0)
     	{
     		continue;
     	}

     	// int i;
      //     for (i = 0; temp[i] != '\0' && temp[i] != '='; i++);
      //     if (temp[i] == '\0')
      //          continue;

     	char temp2[100];
     	sscanf(temp, "M%*d=%[^\n]s\n", temp2);

     	char *p = strtok(temp2, " ");
     	int v1;
     	v1 = p[1] - '0';
     	p = strtok(NULL, " ");
     	while(p != NULL){
     		int v2;
     		v2 = p[1] - '0';
     		add_edge(ret.graph, v1, v2);
     		v1 = v2;
     		p = strtok(NULL, " ");
     	}
     	if (feof(f))
     	{
     		break;
     	}
     }
     fclose(f);
     return ret;
}

















