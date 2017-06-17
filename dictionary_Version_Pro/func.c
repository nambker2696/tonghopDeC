
void xoakytu(char str[100],int vitri){
	int n=strlen(str);
	for(int i=vitri;i<n;i++){
		str[i]=str[i+1];
	}

}
void xoakhoangtrangcuoichuoi(char str[100]){
	int k=strlen(str)-1;
	while (str[k]==32){
		xoakytu(str,k);
		k=strlen(str)-1;
	}
}
// ham them tu vao dic
int addWordToDic(BTA *dic,char *word,char *mean){
	int rsize;
	if(btsel(dic,word,mean,(MAXLEN_MEAN)*sizeof(char),&rsize)==0) {
		return 0;
	} else {
		btins(dic,word,mean,(MAXLEN_MEAN)*sizeof(char));
	}
	return 1;
}
// ham them tu vao soud
int addWordToSou(BTA *sou,char *word,char *mean){
	int rsize;
	char sound[MAXLEN_WORD];
	if(btsel(sou,word,sound,MAXLEN_WORD*sizeof(char),&rsize)==0) {
		if(strstr(sound,mean)==NULL && (strlen(sound)+strlen(mean))<MAXLEN_WORD){
			strcat(sound,"\n");
			strcat(sound,mean);
			btupd(sou,word,sound,MAXLEN_WORD*sizeof(char));
		}
		return 0;
	} else {
		btins(sou,word,sound,MAXLEN_WORD*sizeof(char)); 
	}
	return 1;
}

void docfile(){
	// doc file
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	char sound[MAXLEN_WORD];

	FILE *f = fopen(FILE_READ,"r");
	btinit();
	sou = btopn(NAME_SOUND_TREE,0,0);  
	dic = btopn(NAME_DIC_TREE,0,0);

	if(dic == NULL)
		dic = btcrt(NAME_DIC_TREE,0,FALSE);
	if(sou == NULL)
		sou = btcrt(NAME_SOUND_TREE,0,FALSE);
	if((dic == NULL)|| (sou == NULL))
		exit(1);

	if(!f){
		printf("Cann't open file data\n");
		exit(1);
	}
	while(fscanf(f,"%[^\t]\t%[^\n]\n",word,mean)>0){
		xoakhoangtrangcuoichuoi(word);
		addWordToDic(dic,word,mean);
		soundEx(sound,word,150,1);
		addWordToSou(sou,sound,word);
		
	}
	fclose(f);	
}

void ghifile(){
	FILE *f=fopen("library/data/data3.txt","w");;
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	int i,rsize;
	long j=0;
	i=bfndky(dic,"1",&rsize);
	if(i==0){
		j++;
	} 
	j=0;
	while(bnxtky(dic,word,&i)==0){
		btsel(dic,word,mean,MAXLEN_MEAN*sizeof(char),&rsize);
		if(j==0){
			j=1;
		}
		else{
			fprintf(f,"%s\t%s\n",word,mean);
		}
		j++;
	}
	fclose(f);
}
static GtkEntryCompletion* create_completion_widget(void)
{
	GtkEntryCompletion *completion;
	GtkListStore *store;
	GtkTreeIter iter;
	completion = gtk_entry_completion_new();
	store = gtk_list_store_new(1, G_TYPE_STRING);
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];

	gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(store));
	g_object_unref(store);
	gtk_entry_completion_set_text_column(completion, 0);

	int size;
	gtk_list_store_clear(GTK_LIST_STORE(store));
	btpos(dic,1);
	while(btseln(dic,word,mean,MAXLEN_MEAN*sizeof(char),&size)==0){
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,word,-1);
	}
	return completion;
}