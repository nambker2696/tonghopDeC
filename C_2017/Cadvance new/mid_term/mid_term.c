#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility.h>
//use mfflush after scanning string !!!

typedef struct friend_s {
     char name[100];
} friend;

typedef struct map_s {
     friend *friends_list;
     int friend_num;
     graph graph;
} map;

map data;

int output[100], n, extraOutput[100];
int relaNum;
int vNum;

map get_data_from_file(const char *file_name);
int findFriend(char* friendName, map g);
int findIndex(char* friendName, map g);
void PRINT_ADJACENT_FRIENDS(int v);
void findAdjacentFriend(char* friendName);
void printFriends();

int findID(char *candidate) {
    int i;
    for (i=0; i<vNum; ++i) {
        if ( !strcmp(data.friends_list[i].name, candidate) )
            return i;
    }
    return -1;
}


int main(int argc, char const *argv[])
{
	if (argc != 2) {
          printf("%s\n./%s %s", "WRONG FORMAT !!\n", argv[0],
                 ".graph file"
                );
          exit(1);
     }

    char givenName[100];


     data = get_data_from_file(argv[1]);
     vNum = data.friend_num;

    printf("Cau hoi 1:\n");
    printf("Tong so dinh cua do thi: %d\n", vNum);
    printf("Tong so cung cua do thi: %d\n", relaNum);
    printf("\n");
    printf("Cau hoi 2:\n");
    int id = -1;
    while(id == -1){
    	printf("Enter the friend name: ");	
    	scanf("%[^\n]s", givenName);
    	mfflush();
    	id = findID(givenName);
    	if (id == -1)
            puts ("This name doesn't exist. Input again.\n");
    }
    findAdjacentFriend(givenName);
    printf("\n");
    printf("Cau hoi 3:\n");
    printFriends();
    // printf("Cau hoi 4:\n");
    // printf("Enter the friend name: ");	
    // scanf("%[^\n]s", givenName);
    // mfflush();






    // data = get_data_from_file(argv[1]);
    // switch(get_menu("Option 1;Option 2;Option 3;Option 4;Option 5", 5, 1)){
    // 	case 1:
    // 		break;
    // 	case 2:
    // 		break;
    // 	case 3:
    // 		break;
    // 	case 4:
    // 		break;
    // 	case 5:
    // 		break;
    // }

	return 0;
}

int findFriend(char* friendName, map g){
	int i;
	for (i = 0; i < g.friend_num; i++)
	{
		if (strcmp(g.friends_list[i].name, friendName) == 0)
		{
			return 0;
		}
	}
	return 1;
}

int findIndex(char* friendName, map g){
	int i;
	for (i = 0; i < g.friend_num; i++)
	{
		if (strcmp(g.friends_list[i].name, friendName) == 0)
		{
			return i+1;
		}
	}
	return 0;
}

map get_data_from_file(const char* file_name){
	FILE *f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "Can't Open file %s !!\n", file_name);
        exit(1);
    }

	int MAX = 30;
    map ret;
    ret.friends_list = (friend *)malloc(sizeof(friend) * MAX);
    ret.friend_num = 0;
    ret.graph = create_graph();

    //first line
    char temp[100];
    fgets(temp, 100, f);
    sscanf(temp, "%d", &relaNum);


    char name1[100], name2[100];
    int i1, i2;
    while(1){
    	fgets(temp, 100, f);
    	if (strcmp(temp, "\n") == 0)
     	{
     		continue;
     	}

     	//parsing
     	sscanf( temp, "\"%[^\"]\" \"%[^\"]\"", name1, name2);	//true


     	if (findFriend(name1, ret) == 1)		//new record to add
     	{
     		sscanf(name1, "%s", ret.friends_list[ret.friend_num].name);
     		ret.friend_num++;
     		i1 = ret.friend_num;
     	}else{
     		//table has that record
     		i1 = findIndex(name1, ret);

     	}

     	if (findFriend(name2, ret) == 1)
     	{
     		sscanf(name2, "%s", ret.friends_list[ret.friend_num].name);
     		ret.friend_num++;
     		i2 = ret.friend_num;
     	}else{
     		i2 = findIndex(name2, ret);
     	}



     	//add edges
     	add_edge(ret.graph, i1, i2);


     	if (feof(f))
     	{
     		break;
     	}

    }

    fclose(f);
	return ret;
}

void findAdjacentFriend(char *friendName){
	int i;
	for (i = 0; i < data.friend_num; i++)
	{
		if (strcmp(data.friends_list[i].name, friendName) == 0)
		{
			PRINT_ADJACENT_FRIENDS(i+1);
			break;
		}
	}

}  

int findAdjacentFriendVerticeNum(char *friendName){
	int i;
	for (i = 0; i < data.friend_num; i++)
	{
		if (strcmp(data.friends_list[i].name, friendName) == 0)
		{
			return i+1;
		}
	}
	return 0;
}  


void PRINT_ADJACENT_FRIENDS(int v){
	n = get_adjacent_vertices(data.graph, v, output);                  
    if(n == 0)                                                
        printf("No friends of %s\n", data.friends_list[v-1].name);     
    else{                                                     
        printf("Friends of %s: ", data.friends_list[v-1].name);   
		int i;
		printf("\n");
        for(i = 0; i < n; i++)                               
            printf("%10s", data.friends_list[output[i]-1].name);                       
        printf("\n");                                        
	}     
}

void printFriends(){
	char oneFriend[10][100], twoFriends[10][100], threeFriends[10][100], fourFriends[10][100], fiveFriends[10][100];
	int i;
	int ind1 = 0, ind2 = 0, ind3 = 0, ind4 = 0, ind5 = 0;
	for (i = 0; i < data.friend_num; i++)
	{
		n = get_adjacent_vertices(data.graph, i+1, output);
		if (n == 1)
		{
			strcpy(oneFriend[ind1], data.friends_list[i].name);
			ind1 ++;
		}else if(n == 2)
		{
			strcpy(twoFriends[ind2], data.friends_list[i].name);
			ind2 ++;
		}else if(n == 3){
			strcpy(threeFriends[ind3], data.friends_list[i].name);
			ind3 ++;
		}else if(n == 4){
			strcpy(threeFriends[ind4], data.friends_list[i].name);
			ind4 ++;
		}else if(n == 5){
			strcpy(threeFriends[ind5], data.friends_list[i].name);
			ind5 ++;
		}
	}
	printf("1\t");
	for (i = 0; i < ind1; i++)
	{
		printf("\"%s\"",oneFriend[i]);
	}
	printf("\n");
	printf("2\t");
	for (i = 0; i < ind2; i++)
	{
		printf("\"%s\"",twoFriends[i]);
	}
	printf("\n");
	printf("3\t");
	for (i = 0; i < ind3; i++)
	{
		printf("\"%s\"",threeFriends[i]);
	}
	printf("\n");
	printf("4\t");
	for (i = 0; i < ind4; i++)
	{
		printf("\"%s\"",fourFriends[i]);
	}
	printf("\n");
	printf("5\t");
	for (i = 0; i < ind5; i++)
	{
		printf("\"%s\"",fiveFriends[i]);
	}
	printf("\n");

}

// void getMutualFriends() {
//     char person[m100];
//     int id =-1;
//     printf("Find Mutual Friends:\n");
//     while( id == -1 ){
//         printf ("Enter user name: ");
//         fgets (person, maxn, stdin); person[strlen(person)-1] = '\0';
//         id = findID(person);
//         if (id == -1)
//             puts ("This name doesn't exist. Input again.\n");
//     }
//     int i;
//     int *dist = (int *)malloc(V);
//     bfs (G, id, -1, dist, NULL);
//     printf ("Mutual friends of %s: ",person);
//     int count=0;
//     for (i=0; i<V; ++i)
//         if ( dist[i] == 2 )
//         {
//             printf ("%s ", name[i]);
//             count++;
//         }
//     if (count==0)
//         printf("%s doesnt have any mutual friend.\n",person);
//     puts ("");
//     puts ("");
// }              



