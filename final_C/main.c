#include <stdio.h>
#include "jrb_graph2.h"



void reaFile_History(){
	printf("History");
}

void menu()
{
  printf("==================================================================\n");
  printf("============== CHUONG TRINH  ==============\n");
  printf("==================================================================\n");
  printf("\n 1. In danh sach san pham.\n");
  printf(" 2. In danh sach giao dich.\n");
  printf(" 3. Hien thi muc d lien quan giua 2 san pham.\n");
  printf(" 4. In danh sach cac san pham lien quan.\n");
  printf(" 5. Hien thi moi lien he giua 2 san pham.\n");
  printf(" 6. Thoat.\n");
  printf("\n=====> Nhap lua chon : ");
}

int luachon(void (*menu)(void ))
{
  int luachon;
  do
    {
      menu();
      while(scanf("%d",&luachon)!=1)
	{
	  while(getchar()!='\n');
	  printf("\n  !!! Nhap sai! Hay nhap vao so tu 1 den 6!\n");
	  menu();
	}
      while(getchar()!='\n');
      if(luachon<1||luachon> 6 )
	printf("\n  !!! Nhap sai! Hay nhap vao so tu 1 den 6 !\n");
    }
  while(luachon<1||luachon> 6);
  return luachon;
}

int main(int argc, char *argv[]){

	graph g;
	g = create_graph();
	int n;
	IS is;
	is = new_inputstruct("orderhistory.txt");
	int weigh = 0;
	JRB cur;
	int ver[15];
	int dem;
	int i;
	int trongso;
	int trongso1;
	int trongso2;
	int sp1,sp2;

	while(n!=6){
	    n=luachon(menu);
	    switch(n){
			case 1:{
		    	IS is;
				is = new_inputstruct("products.txt");
				if(is == NULL){
					printf("File products.txt ko the mo dc:\n");
					exit(0);
				}
				while(get_line(is) >= 0){ 
					if(is->NF == 2){  
						add_ver(g, atoi(is->fields[0]), new_jval_s(strdup(is->fields[1])));
						printf("Ma san pham: %s\nTen san pham: %s\n\n",is->fields[0],is->fields[1]);
					}
				}
				jettison_inputstruct(is);
		    	printf("\n");
		    	break;
			}
			case 2:{


				if(is == NULL){
					printf("File orderhistory.txt ko the mo dc:\n");
					exit(0);
				}
				while(get_line(is) >= 0){
					if (is->NF == 3) {
						
					    // dem = indegree(g, atoi(is->fields[0]), ver);
					    // printf("%d\n", dem);
					    // for (i = 0; i < dem; i++) {
					    //   cur = jrb_find_int(g.vers, ver[i]);
					    //   printf("%d %s\n", cur->key, cur->val);
					    // }
					    trongso = get_weight_i(g,atoi(is->fields[0]), atoi(is->fields[1]));
					    trongso1 = get_weight_i(g,atoi(is->fields[0]), atoi(is->fields[2]));
					    trongso2 = get_weight_i(g,atoi(is->fields[1]), atoi(is->fields[2]));

					    if(trongso == 0){
					    	add_edge(g, atoi(is->fields[0]), atoi(is->fields[1]), new_jval_i(1));
					    	add_edge(g, atoi(is->fields[1]), atoi(is->fields[0]), new_jval_i(1));
					    }
					    else{
					    	trongso = trongso+1;
					    	del_edge(g, atoi(is->fields[0]), atoi(is->fields[1]));
					    	del_edge(g, atoi(is->fields[1]), atoi(is->fields[0]));

					    	add_edge(g, atoi(is->fields[0]), atoi(is->fields[1]), new_jval_i(trongso));
					    	add_edge(g, atoi(is->fields[1]), atoi(is->fields[0]), new_jval_i(trongso));
					    }
					    
					    if(trongso1 == 0){

					    	add_edge(g, atoi(is->fields[0]), atoi(is->fields[2]), new_jval_i(1));
					    	add_edge(g, atoi(is->fields[2]), atoi(is->fields[0]), new_jval_i(1));
					    }
					    else{
					    	trongso1 = trongso1+1;
					    	del_edge(g, atoi(is->fields[0]), atoi(is->fields[2]));
					    	del_edge(g, atoi(is->fields[2]), atoi(is->fields[0]));

					    	add_edge(g, atoi(is->fields[0]), atoi(is->fields[2]), new_jval_i(trongso1));
					    	add_edge(g, atoi(is->fields[2]), atoi(is->fields[0]), new_jval_i(trongso1));
					    }
					    
					    if(trongso2 == 0){
					    	add_edge(g, atoi(is->fields[1]), atoi(is->fields[2]), new_jval_i(1));
					    	add_edge(g, atoi(is->fields[2]), atoi(is->fields[1]), new_jval_i(1));
					    }
					    else{
					    	trongso2 = trongso2+1;
					    	del_edge(g, atoi(is->fields[1]), atoi(is->fields[2]) );
					    	del_edge(g, atoi(is->fields[2]), atoi(is->fields[1]) );

					    	add_edge(g, atoi(is->fields[1]), atoi(is->fields[2]), new_jval_i(trongso2));
					    	add_edge(g, atoi(is->fields[2]), atoi(is->fields[1]), new_jval_i(trongso2));
					    }
					    printf("%s %s %s\n",get_val(g.vers,atoi(is->fields[0])),get_val(g.vers,atoi(is->fields[1])),get_val(g.vers,atoi(is->fields[2])) );
					}
				}

		    	break;	
			}
			case 3:{
				
				printf("Nhap 2 san pham:"); 
				scanf("%d %d",&sp1,&sp2);
				trongso = get_weight_i(g,sp1,sp2);
				if(trongso == 0){
					printf("-1");
				}
				else{
					printf("Do lien quan 2 san pham:%d\n",trongso);
				}
				printf("\n");
		    	break;	
			}
			case 4:{
				int spNew;
				printf("Nhap vao ma san pham:");
				scanf("%d",&spNew);
				dem = indegree(g, spNew, ver);
				printf("Cac san pham lien quan:");
			    for (i = 0; i < dem; i++) {
			      cur = jrb_find_int(g.vers, ver[i]);
			      printf("%s ",cur->val);
			    }

				printf("\n");
		    	break;	
			}
			case 5:{
				printf("Nhap 2 san pham:"); 
				scanf("%d %d",&sp1,&sp2);
				int result;
				result = get_all_ways(g,sp1,sp2,ver);
				if(result == 0){
					printf("Hai san pham nay khong co lien he voi nhau\n");
				}
				else{
					for(i = 0; i < result; i++){
						cur = jrb_find_int(g.vers,ver[i]); // tim dinh noi voi argv[3]
						printf("%d %s\n",cur->key,cur->val);
					}				
				}
				printf("\n");
		    	break;	
				printf("\n");
		    	break;	
			}

		}
	}
	return 0;
	drop_graph(g);
}