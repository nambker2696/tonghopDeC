 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "library/inc/bt.h"
#include <time.h>

BTA *dic;
typedef struct{
	long* english;
	long* vietnam;
}data;
data dulieu[3500];

void del(){
	while(getchar() != '\n');
}
int main(int argc, char** argv){


char* trim (char*a){
  int i=0;
  char *s;
  while(a[i]==' '){
    i++;
  }
  s=a+i;
  return s;
}

	int k=0;
	long word1[100];
	long mean1[100];
	FILE *f = fopen("file1.txt","rt");

	while(fscanf(f,"%[^\n]\n",word1)>0){
		dulieu[k].english=(long*)malloc(strlen(word1)*sizeof(long));
		strcpy(dulieu[k].english,word1);
		// printf("\n%d:%s",k, dulieu[k].english);
		k++;
	}
	k=0;
	FILE *f2 = fopen("file2.txt","rt");
	while(fscanf(f2,"%[^\n]\n",mean1)>0){
		dulieu[k].vietnam=(long*)malloc(strlen(mean1)*sizeof(long));
		strcpy(dulieu[k].vietnam,mean1);
		// printf("\n%d:%s",k, dulieu[k].vietnam);
		k++;
	}
	fclose(f);	
	fclose(f2);	


	printf("%d\n",k );
	FILE *f3 = fopen("file3.txt","w+");
	int i;
	for (i = 0; i < k-1;i++){
		printf("%s\n",dulieu[i].english);
		printf("%s\n",dulieu[i].vietnam);
		fprintf(f3, "%s\t%s\n",dulieu[i].english,dulieu[i].vietnam);
	}
	fclose(f3);


	char *dm;
	del();
	scanf("%[^\n]",dm);
	printf("%s\n",&dm );
	char *kq;
	kq = trim(dm);
	printf("%s\n",&kq );
}

